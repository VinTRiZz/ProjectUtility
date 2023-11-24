#include "mainwindow.h"
#include "ui_mainwindow.h"

#define REMOVE_BUTTON_FOCUS(buttonName)                     ui->buttonName##_pushButton->setFocusPolicy(Qt::NoFocus)
#define CONNECT_CLICKED(buttonName, mainWindowFunction)    connect(ui->buttonName##_pushButton, &QPushButton::clicked, this, &MainWindow::mainWindowFunction)


// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// -------------------------------- Signal funciton ------------------------------------- //
// -------------------------------------------------------------------------------------- //
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
    CONNECT_CLICKED(reloadGraph, reloadGraph);
    CONNECT_CLICKED(generateProject, generateProject);

    connect(ui->projects_listWidget, &QListWidget::currentTextChanged, this, &MainWindow::loadDependencyList);
    connect(ui->projects_listWidget, &QListWidget::clicked, this, &MainWindow::projectSelected);

    connect(ui->basePath_lineEdit, &QLineEdit::returnPressed, this, &MainWindow::updateProjectList);

    connect(ui->search_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForLibrary);
    connect(ui->searchProject_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForProject);
    connect(ui->recursiveSearch_lineEdit, &QLineEdit::returnPressed, this, &MainWindow::recursiveDependencySearch);

    connect(ui->menuBar, &QMenuBar::triggered, this, &MainWindow::changedMenu);

    connect(ui->apps_radioButton, &QRadioButton::clicked, this, &MainWindow::fillProjectList);
    connect(ui->libs_radioButton, &QRadioButton::clicked, this, &MainWindow::fillProjectList);

    connect(&m_fileInterface, &ProjectUtility::ProjectDirectoryFileInterface::archiveComplete, this, &MainWindow::archiveComplete);
    connect(&m_fileInterface, &ProjectUtility::ProjectDirectoryFileInterface::buildComplete, this, &MainWindow::buildComplete);

    connect(ui->cleanOutput_pushButton, &QPushButton::clicked, ui->notifications_listWidget, &QListWidget::clear);
    connect(ui->cleanOutput_pushButton, &QPushButton::clicked, ui->log_plainTextEdit, &QPlainTextEdit::clear);
    connect(&m_fileInterface, &ProjectUtility::ProjectDirectoryFileInterface::log, this, &MainWindow::log);
}





// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// ------------------------------------ Setup widget ------------------------------------ //
// -------------------------------------------------------------------------------------- //
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
    REMOVE_BUTTON_FOCUS(reloadGraph);
    REMOVE_BUTTON_FOCUS(cleanOutput);
    REMOVE_BUTTON_FOCUS(generateProject);
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







// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// ----------------------------- Lib list edit functions -------------------------------- //
// -------------------------------------------------------------------------------------- //
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



void MainWindow::saveChanges()
{
    m_fileInterface.saveChanges();
    emit printInfo("Изменения сохранены");
}







// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// ------------------------------- Search funcitons ------------------------------------- //
// -------------------------------------------------------------------------------------- //
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





// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// ------------------------------- Data load functions ---------------------------------- //
// -------------------------------------------------------------------------------------- //
void MainWindow::projectSelected()
{
    auto pItem = ui->projects_listWidget->currentItem();

    if (!pItem)
        return;

    if (ui->autoName_checkBox->isChecked())
        ui->archivePath_lineEdit->setText(pItem->text());
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

    ui->avaliableLibs_listWidget->clear();
    ui->addedLibs_listWidget->clear();

    int parsedFilesCount = m_fileInterface.processDirectory(basePath);

    if (!parsedFilesCount)
    {
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
