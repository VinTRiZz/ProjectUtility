#include "mainwindow.h"
#include "ui_mainwindow.h"

#define CURRENT_VERSION_STRING "v.1.6.2"

enum MENU_INDEX
{
    DEPENDS,
    MISC,
    GENERATORS,
    SETTINGS
};

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    m_fileInterface(this)
{
    ui->setupUi(this);

    ui->menu_stackedWidget->setCurrentIndex(MENU_INDEX::DEPENDS);

    m_depGraphWidget = new GraphWidget::DependencyGraphWidget(this);
    this->setWindowTitle( this->windowTitle() + CURRENT_VERSION_STRING );
    emit updatePercent(0);
    ui->graph_scrollArea->setWidget(m_depGraphWidget);

    m_fileInterface.setGraphWidget(m_depGraphWidget);

    m_fileInterface.loadConfiguration();

    setupAvailableLibrariesView();
    setupSignals();
    setupSettings();

    removeButtonFocuses();

    if (m_fileInterface.configuration().strSettings["Automatic project list update"] == "true")
    {
        emit updateProjectList();
    }
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
        ui->menu_stackedWidget->setCurrentIndex(MENU_INDEX::DEPENDS);
    } else if (menuAction->text() == "Разное")
    {
        ui->menu_stackedWidget->setCurrentIndex(MENU_INDEX::MISC);
    } else if (menuAction->text() == "Генератор проектов")
    {
        ui->menu_stackedWidget->setCurrentIndex(MENU_INDEX::GENERATORS);
    } else if (menuAction->text() == "Настройки")
    {
        ui->menu_stackedWidget->setCurrentIndex(MENU_INDEX::SETTINGS);
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
