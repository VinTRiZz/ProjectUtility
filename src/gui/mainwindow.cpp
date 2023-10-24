#include "mainwindow.h"
#include "ui_mainwindow.h"

#define PRINT(what)     ui->statusBar->showMessage(what, 3000);

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    int parsedFilesCount = m_fileInterface.searchForFiles("/home/lazarev_as/workspace/project");

    if (!parsedFilesCount)
    {
        PRINT("No files found");
        return;
    }
    PRINT(QString("Found some dependency files: %1").arg(QString::number(parsedFilesCount)));
}

MainWindow::~MainWindow()
{
    delete ui;
}
