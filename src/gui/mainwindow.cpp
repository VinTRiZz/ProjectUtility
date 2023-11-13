#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "projectsettings.h" // To change all

#include <QFileInfo>
#include <QThread>

#include <QDebug>

#define REMOVE_BUTTON_FOCUS(buttonName)                     ui->buttonName##_pushButton->setFocusPolicy(Qt::NoFocus)
#define CONNECT_CLICKED(buttonName, mainWindowFunction)    connect(ui->buttonName##_pushButton, &QPushButton::clicked, this, &MainWindow::mainWindowFunction)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_depGraphWidget(new GraphWidget::DependencyGraphWidget(this)),
    m_fileInterface(this, m_depGraphWidget)
{
    ui->setupUi(this);

    ui->menu_stackedWidget->setCurrentIndex(0);
    m_progressPercent.store(100);

    ui->graph_scrollArea->setWidget(m_depGraphWidget);

    setupAvailableLibrariesView();
    setupSignals();
    setupSettings();

    removeButtonFocuses();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSelectedLibrary()
{
    auto pItem = ui->avaliableLibs_listWidget->currentItem();
    if (!pItem)
    {
        emit printInfo("Библиотека не выбрана");
        return;
    }

    QString libraryName = pItem->text();

    if (ui->addedLibs_listWidget->findItems(libraryName, Qt::MatchExactly).size() > 0)
    {
        emit printInfo("Уже в списке зависимостей");
        return;
    }

    auto pProjectItem = ui->projects_listWidget->currentItem();
    if (!pProjectItem)
    {
        emit printInfo("Не выбран проект");
        return;
    }

    const QString currentProjectName = pProjectItem->text();
    if (currentProjectName == libraryName)
    {
        emit printInfo("Не добавлено: Выбрана одномённая с проектом библиотека");
        return;
    }

    if (!m_fileInterface.addLibrary(currentProjectName, libraryName))
    {
        emit printInfo("Не добавлено: Обнаружена циклическая зависимость");
        return;
    }
    ui->addedLibs_listWidget->addItem( libraryName );

    emit printInfo("Зависимость добавлена");
}

void MainWindow::removeSelectedLibrary()
{
    auto pItem = ui->addedLibs_listWidget->currentItem();
    if (!pItem)
    {
        emit printInfo("Библиотека не выбрана");
        return;
    }

    auto pProjectItem = ui->projects_listWidget->currentItem();
    if (!pProjectItem)
    {
        emit printInfo("Не выбран проект");
        return;
    }

    m_fileInterface.removeLibrary(pProjectItem->text(), pItem->text());
    delete ui->addedLibs_listWidget->currentItem();

    emit printInfo("Зависимость удалена");
}

void MainWindow::loadDependencyList(const QString & projectName)
{
    if (projectName.size() == 0)
        return;

    auto deps = m_fileInterface.getDepends(projectName);

    ui->addedLibs_listWidget->clear();
    for (auto & dep : deps)
        ui->addedLibs_listWidget->addItem( dep );
    emit printInfo("Зависимости загружены");
}

void MainWindow::saveChanges()
{
    m_fileInterface.saveChanges();
    emit printInfo("Изменения сохранены");
}

void MainWindow::removeFiles()
{
    if (ui->projects_listWidget->count() == 0)
    {
        emit printInfo("Проекты не найдены, чистки не будет");
        return;
    }

    emit printInfo("Анализ директорий...");

    int filesToRemove = FileWork::FILE_REMOVE_TYPE::NO_FILE;

    if (ui->bin_checkBox->isChecked())
        filesToRemove |= FileWork::FILE_REMOVE_TYPE::BIN;

    if (ui->build_checkBox->isChecked())
        filesToRemove |= FileWork::FILE_REMOVE_TYPE::BUILD;

    if (ui->lib_checkBox->isChecked())
        filesToRemove |= FileWork::FILE_REMOVE_TYPE::LIB;

    if (ui->makeFiles_checkBox->isChecked())
        filesToRemove |= FileWork::FILE_REMOVE_TYPE::MAKEFILE;

    if (ui->qmakeStash_checkBox->isChecked())
        filesToRemove |= FileWork::FILE_REMOVE_TYPE::QMAKE_STASH;

    QStringList fileList = m_cleaner.getFileList(m_fileInterface.currentDirectory(), filesToRemove);

    emit printInfo("Проверка найденных файлов...");

    if (!m_cleaner.listIsCorrect(fileList))
    {
        emit printInfo("Найдена ошибка среди удаляемых файлов, ничего не удалено");
        return;
    }

    emit printInfo("Удаление...");

    m_cleaner.removeFiles(fileList);
    emit printInfo("Файлы удалены");
}

void MainWindow::searchForLibrary(const QString &changedText)
{
    auto foundItems = ui->avaliableLibs_listWidget->findItems(changedText, Qt::MatchContains);

    if (foundItems.size() < 1)
        return;

    auto pItem = foundItems[0];
    if (pItem)
        ui->avaliableLibs_listWidget->setCurrentItem(pItem);
}

void MainWindow::searchForProject(const QString &changedText)
{
    auto foundItems = ui->projects_listWidget->findItems(changedText, Qt::MatchContains);

    if (foundItems.size() < 1)
        return;

    auto pItem = foundItems[0];
    if (pItem)
        ui->projects_listWidget->setCurrentItem(pItem);
}

void MainWindow::changedMenu(QAction *menuAction)
{
    if (menuAction->text() == "Зависимости проекта")
    {
        ui->menu_stackedWidget->setCurrentIndex(0);
    } else if (menuAction->text() == "Сборка, чистка и архивация")
    {
        ui->menu_stackedWidget->setCurrentIndex(1);
    } else if (menuAction->text() == "Настройки")
    {
        ui->menu_stackedWidget->setCurrentIndex(2);
    }
}

void MainWindow::build()
{
    if (!ui->projects_listWidget->count())
    {
        emit printInfo("Список проектов пуст, нечего собирать");
        return;
    }

    if (m_progressPercent.load() != 100)
    {
        emit printInfo("Сборка уже ведётся. Проверьте прогресс в меню сборки");
        return;
    }

    ui->progressBar->setValue(0);
    m_progressPercent.store(0);
    projectsToBuild = 0;

    QString target;
    if (ui->debugTarget_radioButton->isChecked())
    {
        target = "debug";
    } else if (ui->releaseTarget_radioButton->isChecked())
    {
        target = "release";
    }

    if (ui->buildAll_radioButton->isChecked())
    {
        projectsToBuild = ui->projects_listWidget->count();

        QString projectName;
        for (int i = 0; (i < projectsToBuild) && (i < ui->projects_listWidget->count()); i++)
        {
            projectName = ui->projects_listWidget->item(i)->text();
            m_fileInterface.addBuild(projectName, target);
            emit printInfo(QString("Проект %1 добавлен в очередь сборки с целью %2").arg(projectName, target));
        }
    }
    else if (ui->buildCurrent_radioButton->isChecked())
    {

        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            emit printInfo("Проект не выбран");
            return;
        }

        projectsToBuild = 1;

        const QString projectName = pItem->text();

        m_fileInterface.addBuild(projectName, target);

        emit printInfo(QString("Проект %1 добавлен в очередь сборки с целью %2").arg(projectName, target));
    }

    if (m_fileInterface.startBuild())
        emit printInfo("Сборка запущена");
    else
        emit printInfo("Ошибка запуска сборки проектов");
}

void MainWindow::rebuild()
{
    if (!ui->projects_listWidget->count())
    {
        emit printInfo("Список проектов пуст, нечего пересобирать");
        return;
    }

    if (m_progressPercent.load() != 100)
    {
        emit printInfo("Сборка уже ведётся. Проверьте прогресс в меню сборки");
        return;
    }
    ui->progressBar->setValue(0);

    m_progressPercent.store(0);
    projectsToBuild = 0;

    QString target;
    if (ui->debugTarget_radioButton->isChecked())
    {
        target = "debug";
    } else if (ui->releaseTarget_radioButton->isChecked())
    {
        target = "release";
    }

    if (ui->buildAll_radioButton->isChecked())
    {
        projectsToBuild = ui->projects_listWidget->count();
        QString projectName;

        for (int i = 0; (i < projectsToBuild) && (i < ui->projects_listWidget->count()); i++)
        {
            projectName = ui->projects_listWidget->item(i)->text();
            m_fileInterface.addRebuild(projectName, target);
            emit printInfo(QString("Проект %1 добавлен в очередь пересборки с целью %2").arg(projectName, target));
        }
    }
    else if (ui->buildCurrent_radioButton->isChecked())
    {
        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            emit printInfo("Проект не выбран");
            return;
        }

        projectsToBuild = 1;

        const QString projectName = pItem->text();

        m_fileInterface.addRebuild(projectName, target);

        emit printInfo(QString("Проект %1 добавлен в очередь пересборки с целью %2").arg(projectName, target));
    }

    if (m_fileInterface.startBuild())
        emit printInfo("Начата пересборка");
    else
        emit printInfo("Ошибка запуска пересборки проектов");
}

void MainWindow::printInfo(const QString & what)
{
    ui->notifications_listWidget->addItem(what);
    ui->notifications_listWidget->scrollToBottom();
}

void MainWindow::archiveComplete()
{
    if (m_fileInterface.archiveSucceed())
        emit printInfo("Архив создан");
    else
        emit printInfo("Ошибка создания архива");
}

void MainWindow::archive()
{
    if (ui->archiveAll_radioButton->isChecked())
    {
        const QString archivePath = ui->archivePath_lineEdit->text();

        m_fileInterface.archiveAllProjects(archivePath);

    } else if (ui->archiveSelected_radioButton->isChecked())
    {
        const QString archivePath = ui->archivePath_lineEdit->text();

        QStringList projectNames;
        auto selectedItems = ui->projects_listWidget->selectedItems();

        for (auto * pItem : selectedItems)
            projectNames << pItem->text();

        m_fileInterface.archiveSelectedProjects(projectNames, archivePath);

    } else if (ui->archiveCurrent_radioButton->isChecked())
    {
        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            emit printInfo("Проект не выбран");
            return;
        }

        const QString archivePath = ui->archivePath_lineEdit->text();
        const QString projectName = pItem->text();

        m_fileInterface.archiveProject(projectName, archivePath);
    }

    emit printInfo("Архивация запущена");
}

void MainWindow::projectSelected()
{
    auto pItem = ui->projects_listWidget->currentItem();

    if (!pItem)
        return;

    if (ui->autoName_checkBox->isChecked())
        ui->archivePath_lineEdit->setText(pItem->text());
}

void MainWindow::buildComplete(const QString &projectName, const bool result)
{
    if (result)
    {
        emit printInfo(QString("Собран проект %1").arg(projectName));
        m_progressPercent.store(m_progressPercent.load() + 100.0f / (float)projectsToBuild);
        int currentPercent = m_progressPercent.load();
        ui->progressBar->setValue(currentPercent);
    }
    else
    {
        emit printInfo(QString("Ошибка сборки проекта %1. Более полная информация в файле %2").arg(projectName, m_fileInterface.mainConfig().strSettings["BUILD_LOG_FILE_NAME"]));
        m_progressPercent.store(100);
        ui->progressBar->setValue(100);
    }
}

void MainWindow::recursiveDependencySearch()
{
    const QString dependName = ui->recursiveSearch_lineEdit->text();

    auto pItem = ui->projects_listWidget->currentItem();

    if (!pItem)
    {
        emit printInfo("Выберите проект для поиска в нём зависимости");
        return;
    }

    const QString projectName = pItem->text();

    if (dependName.length() < 1)
    {
        emit printInfo("Введите название библиотеки для рекурсивного поиска среди зависимостей проекта");
        return;
    }

    bool hasDepend = m_fileInterface.hasDependRecurse(projectName, dependName);

    if (hasDepend)
        emit printInfo(QString("Проект %1 зависит от библиотеки %2").arg(projectName, dependName));
    else
        emit printInfo(QString("Проект не зависит от этой библиотеки: %1").arg(dependName));

}

void MainWindow::settingClicked()
{
    const QString settingName = ui->settingList_listWidget->currentItem()->text();

    Configuration::StringSetting * pStrSetting {nullptr};
    Configuration::IntSetting * pIntSetting {nullptr};

    for (auto & strSetting : m_fileInterface.mainConfig().strSettings)
    {
        if (strSetting.first == settingName)
            pStrSetting = &strSetting.second;
    }

    if (!pStrSetting)
    {
        for (auto & intSetting : m_fileInterface.mainConfig().intSettings)
        {
            if (intSetting.first == settingName)
                pIntSetting = &intSetting.second;
        }

        if (!pIntSetting)
            return;

        ui->settingValue_label->setText(QString::number(*pIntSetting));
    }
    else
    {
        ui->settingValue_label->setText(*pStrSetting);
    }

    ui->settingName_label->setText(settingName);
    ui->settingValue_lineEdit->clear();
}

void MainWindow::updateSelectedSetting()
{
    const QString settingName = ui->settingName_label->text();

    if (settingName.isEmpty())
    {
        emit printInfo("Настройка не выбрана");
        return;
    }

    const QString settingValue = ui->settingValue_lineEdit->text();

    Configuration::StringSetting * pStrSetting {nullptr};
    Configuration::IntSetting * pIntSetting {nullptr};

    for (auto & strSetting : m_fileInterface.mainConfig().strSettings)
    {
        if (strSetting.first == settingName)
            pStrSetting = &strSetting.second;
    }

    if (!pStrSetting)
    {
        for (auto & intSetting : m_fileInterface.mainConfig().intSettings)
        {
            if (intSetting.first == settingName)
                pIntSetting = &intSetting.second;
        }

        if (!pIntSetting)
            return;

        *pIntSetting = settingValue.toInt();
    }
    else
    {
        *pStrSetting = settingValue;
    }

    ui->settingValue_label->setText(settingValue);
}

void MainWindow::saveSettingsToFile()
{
#warning "Don't save now"
    qDebug() << "\033[32mSettings not saved!\033[0m";
}

void MainWindow::restoreSetting()
{
    const QString settingName = ui->settingName_label->text();

    Configuration::StringSetting * pStrSetting {nullptr};
    Configuration::IntSetting * pIntSetting {nullptr};

    for (auto & strSetting : m_fileInterface.mainConfig().strSettings)
    {
        if (strSetting.first == settingName)
            pStrSetting = &strSetting.second;
    }

    if (pStrSetting)
    {
        *pStrSetting = Configuration::defaultProjectConfiguration.strSettings[settingName];
        return;
    }

    for (auto & intSetting : m_fileInterface.mainConfig().intSettings)
    {
        if (intSetting.first == settingName)
            pIntSetting = &intSetting.second;
    }

    if (!pIntSetting)
        return;

    *pIntSetting = Configuration::defaultProjectConfiguration.intSettings[settingName];
}

void MainWindow::restoreSettingsAll()
{
    m_fileInterface.mainConfig() = Configuration::defaultProjectConfiguration;
    emit printInfo("Все настройки возвращены");
}

void MainWindow::updateProjectList()
{
    basePath = ui->basePath_lineEdit->text();
    if (basePath.size() < 1)
    {
        emit printInfo("Пустой путь");
        return;
    }

    QFileInfo pathTester(basePath);
    if (!pathTester.exists() || !pathTester.isDir())
    {
        basePath.clear();
        emit printInfo("Или это не директория, или такой не существует");
        return;
    }

    int parsedFilesCount = m_fileInterface.processDirectory(basePath);

    if (!parsedFilesCount)
    {
        ui->avaliableLibs_listWidget->clear();
        ui->projects_listWidget->clear();
        ui->addedLibs_listWidget->clear();
        emit printInfo("Ничего не найдено");
        return;
    }

    emit printInfo(QString("Найдено %1 объектов").arg(QString::number(parsedFilesCount)));

    QStringList projectList;

    projectList.append( m_fileInterface.getLibraryNameList() );

    ui->avaliableLibs_listWidget->clear();
    for (QString & proj : projectList)
        ui->avaliableLibs_listWidget->addItem(proj);

    fillProjectList();

    emit printInfo("Проекты загружены");
}

void MainWindow::setupAvailableLibrariesView()
{
    ui->avaliableLibs_listWidget->setFocusPolicy(Qt::NoFocus);
    ui->avaliableLibs_listWidget->setSortingEnabled(true);
}

void MainWindow::setupSignals()
{
    CONNECT_CLICKED(add, addSelectedLibrary);
    CONNECT_CLICKED(remove, removeSelectedLibrary);
    CONNECT_CLICKED(update, updateProjectList);
    CONNECT_CLICKED(clean, removeFiles);
    CONNECT_CLICKED(saveChanges, saveChanges);
    CONNECT_CLICKED(build, build);
    CONNECT_CLICKED(rebuild, rebuild);
    CONNECT_CLICKED(archive, archive);

    connect(ui->projects_listWidget, &QListWidget::currentTextChanged, this, &MainWindow::loadDependencyList);
    connect(ui->basePath_lineEdit, &QLineEdit::returnPressed, this, &MainWindow::updateProjectList);

    connect(ui->search_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForLibrary);
    connect(ui->searchProject_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForProject);

    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::changedMenu);

    connect(ui->apps_radioButton, &QRadioButton::clicked, this, &MainWindow::fillProjectList);
    connect(ui->libs_radioButton, &QRadioButton::clicked, this, &MainWindow::fillProjectList);

    connect(&m_fileInterface, &FileWork::ProjectDirectoryFileInterface::archiveComplete, this, &MainWindow::archiveComplete);

    connect(ui->projects_listWidget, &QListWidget::clicked, this, &MainWindow::projectSelected);

    connect(&m_fileInterface, &FileWork::ProjectDirectoryFileInterface::buildComplete, this, &MainWindow::buildComplete);

    connect(ui->cleanOutput_pushButton, &QPushButton::clicked, ui->notifications_listWidget, &QListWidget::clear);

    connect(ui->recursiveSearch_lineEdit, &QLineEdit::returnPressed, this, &MainWindow::recursiveDependencySearch);
}

void MainWindow::removeButtonFocuses()
{
    // Remove focus
    REMOVE_BUTTON_FOCUS(add);
    REMOVE_BUTTON_FOCUS(remove);
    REMOVE_BUTTON_FOCUS(update);
    REMOVE_BUTTON_FOCUS(clean);
    REMOVE_BUTTON_FOCUS(saveChanges);
    REMOVE_BUTTON_FOCUS(build);
    REMOVE_BUTTON_FOCUS(rebuild);
    REMOVE_BUTTON_FOCUS(archive);
}

void MainWindow::setupSettings()
{
    for (auto & strSetting : m_fileInterface.mainConfig().strSettings)
        ui->settingList_listWidget->addItem(strSetting.first);

    for (auto & intSetting : m_fileInterface.mainConfig().intSettings)
        ui->settingList_listWidget->addItem(intSetting.first);

    connect(ui->settingList_listWidget, &QListWidget::clicked, this, &MainWindow::settingClicked);
    connect(ui->settingAccept_pushButton, &QPushButton::clicked, this, &MainWindow::updateSelectedSetting);
    connect(ui->settingsSave_pushButton, &QPushButton::clicked, this, &MainWindow::saveSettingsToFile);
    connect(ui->settingsRestore_pushButton, &QPushButton::clicked, this, &MainWindow::restoreSettingsAll);
    connect(ui->settingRestore_pushButton, &QPushButton::clicked, this, &MainWindow::restoreSetting);
}

void MainWindow::fillProjectList()
{
    ui->projects_listWidget->clear();
    if (ui->apps_radioButton->isChecked())
    {
        QStringList appList = m_fileInterface.getAppNameList();
        for (QString & app : appList)
            ui->projects_listWidget->addItem(app);
    }
    else if (ui->libs_radioButton->isChecked())
    {
        QStringList libList = m_fileInterface.getLibraryNameList();
        for (QString & lib : libList)
            ui->projects_listWidget->addItem(lib);
    }
}
