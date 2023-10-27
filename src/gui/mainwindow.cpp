#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>
#include <QThread>

#include <QDebug>

#define PRINT(what)     ui->statusBar->showMessage(what, 3000)

#define REMOVE_BUTTON_FOCUS(buttonName)                     ui->buttonName##_pushButton->setFocusPolicy(Qt::NoFocus)
#define CONNECT_CLIECKED(buttonName, mainWindowFunction)    connect(ui->buttonName##_pushButton, &QPushButton::clicked, this, &MainWindow::mainWindowFunction)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->stackedWidget->setCurrentIndex(0);

    setupAvailableLibrariesView();

    updateBasePath(); // For tests

    // Remove focus
    REMOVE_BUTTON_FOCUS(add);
    REMOVE_BUTTON_FOCUS(remove);
    // REMOVE_BUTTON_FOCUS(saveBackup);
    // REMOVE_BUTTON_FOCUS(loadBackup);
    REMOVE_BUTTON_FOCUS(update);
    REMOVE_BUTTON_FOCUS(acceptBasePath);
    REMOVE_BUTTON_FOCUS(clean);
    REMOVE_BUTTON_FOCUS(saveChanges);
    REMOVE_BUTTON_FOCUS(build);
    REMOVE_BUTTON_FOCUS(rebuild);

    CONNECT_CLIECKED(add, addSelectedLibrary);
    CONNECT_CLIECKED(remove, removeSelectedLibrary);
    // CONNECT_CLIECKED(saveBackup, createBackup);
    // CONNECT_CLIECKED(loadBackup, loadBackup);
    CONNECT_CLIECKED(update, updateProjectList);
    CONNECT_CLIECKED(acceptBasePath, updateBasePath);
    CONNECT_CLIECKED(clean, removeFiles);
    CONNECT_CLIECKED(saveChanges, saveChanges);
    CONNECT_CLIECKED(build, build);
    CONNECT_CLIECKED(rebuild, rebuild);

    connect(ui->projects_listWidget, &QListWidget::currentTextChanged, this, &MainWindow::loadDependencyList);

    connect(ui->search_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForLibrary);
    connect(ui->searchProject_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForProject);

    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::changedMenu);

    connect(ui->apps_radioButton, &QRadioButton::clicked, this, &MainWindow::fillProjectList);
    connect(ui->libs_radioButton, &QRadioButton::clicked, this, &MainWindow::fillProjectList);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::addSelectedLibrary()
{
    auto pItem = ui->avaliableLibs_listWidget->currentItem();
    if (!pItem)
        return;

    if (ui->addedLibs_listWidget->findItems(pItem->text(), Qt::MatchExactly).size() > 0)
        return;

    auto pProjectItem = ui->projects_listWidget->currentItem();
    if (!pItem)
        return;

    const QString currentProjectName = pProjectItem->text();
    if (currentProjectName == pItem->text())
    {
        PRINT("Нельзя зависеть от себя!");
        return;
    }

    m_fileInterface.addLibrary(currentProjectName, pItem->text());
    ui->addedLibs_listWidget->addItem( pItem->text() );
}

void MainWindow::removeSelectedLibrary()
{
    auto pItem = ui->addedLibs_listWidget->currentItem();
    if (!pItem)
    {
        PRINT("Не выбрана библиотека");
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
        PRINT("Не выбран проект");
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
    PRINT("Изменения сохранены");
}

void MainWindow::createBackup()
{
    // if (m_fileInterface.backupAll(ui->backupDir_lineEdit->text()))
        PRINT("Бэкап создан");
    // else
        PRINT("Бэкап создан частично или не создан (проверьте путь до директории с бэкапами)");
}

void MainWindow::loadBackup()
{
    // if (m_fileInterface.loadBackup(ui->backupDir_lineEdit->text()))
        PRINT("Бэкап загружен");
    // else
        PRINT("Бэкап загружен частично или не загружен (проверьте путь до директории с бэкапами)");
}

void MainWindow::updateBasePath()
{
    basePath = ui->basePath_lineEdit->text();
    if (basePath.size() < 1)
    {
        PRINT("Пустой путь");
        return;
    }

    QFileInfo pathTester(basePath);
    if (!pathTester.exists() || !pathTester.isDir())
    {
        basePath.clear();
        PRINT("Или это не директория, или такой не существует");
        return;
    }
    updateProjectList();
}

void MainWindow::removeFiles()
{
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
            PRINT("Ошибка в списке файлов на удаление. Ничего не удалено");
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
    if (menuAction->text() == "Управление проектом")
    {
        ui->stackedWidget->setCurrentIndex(0);
    } else if (menuAction->text() == "Зависимости проекта")
    {
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::build()
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
        const int projectCount = ui->projects_listWidget->count();
        QString projectName;

        for (int i = 0; (i < projectCount) && (i < ui->projects_listWidget->count()); i++)
        {
            projectName = ui->projects_listWidget->item(i)->text();
            PRINT(QString("Собирается проект %1 (%2 из %3)").arg(projectName, QString::number(i), QString::number(projectCount)));
            m_fileInterface.build(projectName, target);
        }
        PRINT("Проекты собраны");
    }
    else if (ui->buildCurrent_radioButton->isChecked())
    {
        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            PRINT("Проект не выбран");
            return;
        }

        QString projectName = pItem->text();
        PRINT(QString("Проект %1 собирается...").arg(projectName));
        if (m_fileInterface.build(projectName, target))
        {
            PRINT("Проект собран");
        }
        else
        {
            PRINT("Ошибка сборки. Более полная информация в файле buildLog.txt");
        }
    }
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
        const int projectCount = ui->projects_listWidget->count();
        QString projectName;

        for (int i = 0; (i < projectCount) && (i < ui->projects_listWidget->count()); i++)
        {
            projectName = ui->projects_listWidget->item(i)->text();
            PRINT(QString("Пересобирается проект %1 (%2 из %3)").arg(projectName, QString::number(i), QString::number(projectCount)));
            m_fileInterface.rebuild(projectName, target);
        }
        PRINT("Проекты пересобраны");
    }
    else if (ui->buildCurrent_radioButton->isChecked())
    {
        auto pItem = ui->projects_listWidget->currentItem();

        if (!pItem)
        {
            PRINT("Проект не выбран");
            return;
        }

        QString projectName = pItem->text();
        PRINT(QString("Проект %1 собирается...").arg(projectName));
        if (m_fileInterface.rebuild(projectName, target))
        {
            PRINT("Проект пересобран");
        }
        else
        {
            PRINT("Ошибка пересборки. Более полная информация в файле buildLog.txt");
        }
    }
}

void MainWindow::updateProjectList()
{
    if (basePath.size() < 1)
    {
        PRINT("Неправильный путь");
        return;
    }

    int parsedFilesCount = m_fileInterface.processDirectory(basePath);

    if (!parsedFilesCount)
    {
        PRINT("Ничего не найдено");
        return;
    }
    PRINT(QString("Найдено %1 объектов").arg(QString::number(parsedFilesCount)));

    QStringList projectList;

    // projectList.append( m_fileInterface.getLibraryNameList() );
    projectList.append( m_fileInterface.getAppNameList() );

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
    if (ui->libs_radioButton->isChecked())
    {
        QStringList appList = m_fileInterface.getAppNameList();
        for (QString & app : appList)
            ui->projects_listWidget->addItem(app);
    }
    else if (ui->apps_radioButton->isChecked())
    {
        QStringList libList = m_fileInterface.getLibraryNameList();
        for (QString & lib : libList)
            ui->projects_listWidget->addItem(lib);
    }
}

