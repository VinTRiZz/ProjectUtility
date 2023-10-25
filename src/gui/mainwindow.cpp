#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileInfo>

#include <QDebug>

#define PRINT(what)     ui->statusBar->showMessage(what, 3000)

#define REMOVE_BUTTON_FOCUS(buttonName)                     ui->buttonName##_pushButton->setFocusPolicy(Qt::NoFocus)
#define CONNECT_CLIECKED(buttonName, mainWindowFunction)    connect(ui->buttonName##_pushButton, &QPushButton::clicked, this, &MainWindow::mainWindowFunction)

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupAvailableLibrariesView();

    setBasePath(); // For tests

    // Remove focus
    REMOVE_BUTTON_FOCUS(add);
    REMOVE_BUTTON_FOCUS(remove);
    REMOVE_BUTTON_FOCUS(saveBackup);
    REMOVE_BUTTON_FOCUS(loadBackup);
    REMOVE_BUTTON_FOCUS(update);
    REMOVE_BUTTON_FOCUS(acceptBasePath);
    REMOVE_BUTTON_FOCUS(clean);

    CONNECT_CLIECKED(add, addSelectedLibrary);
    CONNECT_CLIECKED(remove, removeSelectedLibrary);
    CONNECT_CLIECKED(saveBackup, createBackup);
    CONNECT_CLIECKED(loadBackup, loadBackup);
    CONNECT_CLIECKED(update, updateProjectList);
    CONNECT_CLIECKED(acceptBasePath, setBasePath);
    CONNECT_CLIECKED(clean, removeFiles);

    connect(ui->project_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::loadDependencyList);
    connect(ui->search_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForText);
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

    m_fileInterface.addLibrary(ui->project_comboBox->currentText(), pItem->text());
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

    m_fileInterface.removeLibrary(ui->project_comboBox->currentText(), pItem->text());
    delete ui->addedLibs_listWidget->currentItem();
}

void MainWindow::loadDependencyList()
{
    const QString projectName = ui->project_comboBox->currentText();

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

void MainWindow::createBackup()
{
    if (m_fileInterface.backupAll())
        PRINT("Бэкап создан");
    else
        PRINT("Бэкап создан частично или не создан");
}

void MainWindow::loadBackup()
{
    if (m_fileInterface.loadBackup())
        PRINT("Бэкап загружен");
    else
        PRINT("Бэкап загружен частично или не загружен");
}

void MainWindow::setBasePath()
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

    QStringList fileList = m_cleaner.getFileList(m_fileInterface.currentDirectory(), filesToRemove);

    // Check if all's good
    for (QString & file : fileList)
    {
        if (
            !file.contains("/BIN/") &&
            !file.contains("/Makefile") &&
            !file.contains("/BUILD/") &&
            !file.contains("/LIB/")
        )
        {
            qDebug() << "[REMOVE CHECK] Invalid file:[" << file << "]";
            PRINT("Ошибка в списке файлов на удаление. Ничего не удалено");
            return;
        }
    }

    m_cleaner.removeFiles(fileList);
}

void MainWindow::searchForText(const QString &changedText)
{
    auto foundItems = ui->avaliableLibs_listWidget->findItems(changedText, Qt::MatchContains);

    if (foundItems.size() < 1)
        return;

    auto pItem = foundItems[0];
    if (pItem)
        ui->avaliableLibs_listWidget->setCurrentItem(pItem);
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

    QStringList libList = m_fileInterface.getLibraryNameList();

    ui->avaliableLibs_listWidget->clear();
    for (QString & lib : libList)
    {
        ui->avaliableLibs_listWidget->addItem(lib);
    }

    QStringList appList = m_fileInterface.getAppNameList();

    ui->project_comboBox->clear();
    for (QString & app : appList)
    {
        ui->project_comboBox->addItem(app);
    }

    if (appList.size() > 0)
    {
        ui->project_comboBox->setCurrentIndex(0);
        loadDependencyList(); // Cuz ComboBox already selected project
    }
}

void MainWindow::setupAvailableLibrariesView()
{
    ui->avaliableLibs_listWidget->setFocusPolicy(Qt::NoFocus);
    ui->avaliableLibs_listWidget->setSortingEnabled(true);
}
