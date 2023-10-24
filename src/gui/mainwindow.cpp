#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QDebug>

#define PRINT(what)     ui->statusBar->showMessage(what, 3000);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    setupAvailableLibrariesView();

    updateProjectList();

    connect(ui->update_pushButton, &QPushButton::clicked, this, &MainWindow::updateProjectList);
    connect(ui->add_pushButton, &QPushButton::clicked, this, &MainWindow::addSelectedLibrary);
    connect(ui->remove_pushButton, &QPushButton::clicked, this, &MainWindow::removeSelectedLibrary);
    connect(ui->project_comboBox, &QComboBox::currentTextChanged, this, &MainWindow::loadDependencyList);
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
        return;

    m_fileInterface.removeLibrary(ui->project_comboBox->currentText(), pItem->text());
    delete ui->addedLibs_listWidget->currentItem();
}

void MainWindow::loadDependencyList()
{
    const QString projectName = ui->project_comboBox->currentText();

    if (projectName.size() == 0)
        return;

    auto deps = m_fileInterface.getDepends(projectName);

    ui->addedLibs_listWidget->clear();
    for (auto & dep : deps)
        ui->addedLibs_listWidget->addItem( dep );
}

void MainWindow::updateProjectList()
{
    int parsedFilesCount = m_fileInterface.searchForFiles("/home/lazarev_as/workspace/project");

    if (!parsedFilesCount)
    {
        PRINT("No files found");
        return;
    }
    PRINT(QString("Found some dependency files: %1").arg(QString::number(parsedFilesCount)));

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
    loadDependencyList(); // Cuz ComboBox already selected project
}

void MainWindow::setupAvailableLibrariesView()
{
    ui->avaliableLibs_listWidget->setFocusPolicy(Qt::NoFocus);
}

void MainWindow::updateUsedLibraries()
{

}
