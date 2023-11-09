#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QThread>

#include <QDebug>

#define REMOVE_BUTTON_FOCUS(buttonName)                     ui->buttonName##_pushButton->setFocusPolicy(Qt::NoFocus)
#define CONNECT_CLIECKED(buttonName, mainWindowFunction)    connect(ui->buttonName##_pushButton, &QPushButton::clicked, this, &MainWindow::mainWindowFunction)

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

    // Remove focus
    REMOVE_BUTTON_FOCUS(add);
    REMOVE_BUTTON_FOCUS(remove);
    // REMOVE_BUTTON_FOCUS(saveBackup);
    // REMOVE_BUTTON_FOCUS(loadBackup);
    REMOVE_BUTTON_FOCUS(update);
    REMOVE_BUTTON_FOCUS(clean);
    REMOVE_BUTTON_FOCUS(saveChanges);
    REMOVE_BUTTON_FOCUS(build);
    REMOVE_BUTTON_FOCUS(rebuild);
    REMOVE_BUTTON_FOCUS(archive);

    CONNECT_CLIECKED(add, addSelectedLibrary);
    CONNECT_CLIECKED(remove, removeSelectedLibrary);
    // CONNECT_CLIECKED(saveBackup, createBackup);
    // CONNECT_CLIECKED(loadBackup, loadBackup);
    CONNECT_CLIECKED(update, updateProjectList);
    CONNECT_CLIECKED(clean, removeFiles);
    CONNECT_CLIECKED(saveChanges, saveChanges);
    CONNECT_CLIECKED(build, build);
    CONNECT_CLIECKED(rebuild, rebuild);
    CONNECT_CLIECKED(archive, archive);

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
        emit printInfo("Выберите библиотеку");
        return;
    }

    QString libraryName = pItem->text();

    if (ui->addedLibs_listWidget->findItems(libraryName, Qt::MatchExactly).size() > 0)
    {
        emit printInfo("Уже добавлено");
        return;
    }

    auto pProjectItem = ui->projects_listWidget->currentItem();
    if (!pProjectItem)
    {
        emit printInfo("Выберите проект");
        return;
    }

    const QString currentProjectName = pProjectItem->text();
    if (currentProjectName == libraryName)
    {
        emit printInfo("Нельзя зависеть от себя!");
        return;
    }

    if (!m_fileInterface.addLibrary(currentProjectName, libraryName))
    {
        emit printInfo("Обнаружена рекурсивная зависимость! Библиотека не добавлена.");
        return;
    }
    ui->addedLibs_listWidget->addItem( libraryName );
}

void MainWindow::removeSelectedLibrary()
{
    auto pItem = ui->addedLibs_listWidget->currentItem();
    if (!pItem)
    {
        emit printInfo("Не выбрана библиотека");
        return;
    }

    auto pProjectItem = ui->projects_listWidget->currentItem();
    if (!pProjectItem)
        return;

    m_fileInterface.removeLibrary(pProjectItem->text(), pItem->text());
    delete ui->addedLibs_listWidget->currentItem();
}

void MainWindow::loadDependencyList(const QString & projectName)
{
    if (projectName.size() == 0)
    {
        emit printInfo("Не выбран проект");
        return;
    }

    auto deps = m_fileInterface.getDepends(projectName);

    ui->addedLibs_listWidget->clear();
    for (auto & dep : deps)
        ui->addedLibs_listWidget->addItem( dep );
}

void MainWindow::saveChanges()
{
    m_fileInterface.saveChanges();
    emit printInfo("Изменения сохранены");
}

void MainWindow::createBackup()
{
    // if (m_fileInterface.backupAll(ui->backupDir_lineEdit->text()))
        emit printInfo("Бэкап создан");
    // else
        emit printInfo("Бэкап создан частично или не создан (проверьте путь до директории с бэкапами)");
}

void MainWindow::loadBackup()
{
    // if (m_fileInterface.loadBackup(ui->backupDir_lineEdit->text()))
        emit printInfo("Бэкап загружен");
    // else
        emit printInfo("Бэкап загружен частично или не загружен (проверьте путь до директории с бэкапами)");
}

void MainWindow::removeFiles()
{
    if (ui->projects_listWidget->count() == 0)
    {
        emit printInfo("Негде чистить");
        return;
    }

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

    // Check if all's good
    for (QString & file : fileList)
    {
        if (
            !file.contains("/BIN/") &&
            !file.contains("/BUILD/") &&
            !file.contains("/LIB/") &&
            !file.contains("/Makefile") &&
            !file.contains("/.qmake.stash")
        )
        {
            qDebug() << "[REMOVE CHECK] Invalid file:[" << file << "]";
            emit printInfo("Ошибка в списке файлов на удаление. Ничего не удалено");
            return;
        }
    }

    m_cleaner.removeFiles(fileList);
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
    }
}

void MainWindow::build()
{
    if (m_progressPercent.load() != 100)
    {
        emit printInfo("Сборка уже ведётся. Проверьте прогресс в меню сборки");
        return;
    }

    m_progressPercent.store(0);

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
        const int projectCount = ui->projects_listWidget->count();

        for (int i = 0; (i < projectCount) && (i < ui->projects_listWidget->count()); i++)
            m_fileInterface.addBuild(ui->projects_listWidget->item(i)->text(), target);
    }
    else if (ui->buildCurrent_radioButton->isChecked())
    {
        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            emit printInfo("Проект не выбран");
            return;
        }

        m_fileInterface.addBuild(pItem->text(), target);
    }

    if (m_fileInterface.startBuild())
        emit printInfo("Проект(ы) добавлен(ы) в очередь на сборку");
    else
        emit printInfo("Ошибка добавления на сборку");
}

void MainWindow::rebuild()
{
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
        }
    }
    else if (ui->buildCurrent_radioButton->isChecked())
    {
        projectsToBuild = 1;

        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            emit printInfo("Проект не выбран");
            return;
        }

        m_fileInterface.addRebuild(pItem->text(), target);
    }

    if (m_fileInterface.startBuild())
        emit printInfo("Проект(ы) добавлен(ы) в очередь на пересборку");
    else
        emit printInfo("Ошибка добавления на пересборку");
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

        emit printInfo("Архивируется...");

        const QString archivePath = ui->archivePath_lineEdit->text();
        const QString projectName = pItem->text();

        m_fileInterface.archiveProject(projectName, archivePath);
    }
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
    }
    else
    {
        emit printInfo(QString("Ошибка сборки проекта %1. Более полная информация в файле buildLog.txt").arg(projectName));
        m_progressPercent.store(100);
    }
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
    // projectList.append( m_fileInterface.getAppNameList() );

    ui->avaliableLibs_listWidget->clear();
    for (QString & proj : projectList)
    {
        ui->avaliableLibs_listWidget->addItem(proj);
    }

    fillProjectList();
}

void MainWindow::setupAvailableLibrariesView()
{
    ui->avaliableLibs_listWidget->setFocusPolicy(Qt::NoFocus);
    ui->avaliableLibs_listWidget->setSortingEnabled(true);
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

