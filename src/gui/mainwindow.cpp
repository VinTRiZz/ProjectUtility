#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CURRENT_VERSION_STRING "v.1.3.3"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_depGraphWidget(new GraphWidget::DependencyGraphWidget(this)),
    m_fileInterface(this, m_depGraphWidget)
{
    ui->setupUi(this);

    this->setWindowTitle( this->windowTitle() + CURRENT_VERSION_STRING );

    m_fileInterface.loadConfiguration();

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

void MainWindow::printInfo(const QString & what)
{
    ui->notifications_listWidget->addItem(what);
    ui->notifications_listWidget->scrollToBottom();

    qDebug() << "[USER ACTION]" << what;
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


void MainWindow::reloadGraph()
{
    auto pItem = ui->projects_listWidget->currentItem();

    if (!pItem)
    {
        emit printInfo("Проект не выбран");
        return;
    }

    m_fileInterface.reloadGraph();
    m_fileInterface.setCurrentHead(pItem->text());
}

void MainWindow::updatePercent(float newValue)
{
    ui->progressBar->setValue(newValue);
    m_progressPercent.store(newValue);
}
