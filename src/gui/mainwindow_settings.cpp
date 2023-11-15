#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::searchForSetting(const QString &changedText)
{
    auto foundItems = ui->settingList_listWidget->findItems(changedText, Qt::MatchContains);

    if (foundItems.size() < 1)
        return;

    auto pItem = foundItems[0];
    if (pItem)
        ui->settingList_listWidget->setCurrentItem(pItem);
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
        ui->settingValue_lineEdit->setValidator(new QRegExpValidator(QRegExp("[0-9]+"), ui->settingValue_lineEdit));
        ui->settingValue_label->setText(QString::number(*pIntSetting));
    }
    else
    {
        ui->settingValue_lineEdit->setValidator(nullptr);
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
        if ((settingName.contains("path")) && (settingValue.front().toLatin1() != '/') && !settingValue.isEmpty())
        {
            *pStrSetting = "/";
            *pStrSetting += settingValue;
        }
        else
        {
            *pStrSetting = settingValue;
        }
    }

    ui->settingValue_label->setText(settingValue);
}



void MainWindow::saveSettingsToFile()
{
    m_fileInterface.saveCurrentConfiguration();
    emit printInfo("Конфигурация сохранена");
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



void MainWindow::setupSettings()
{
    for (auto & strSetting : m_fileInterface.mainConfig().strSettings)
        ui->settingList_listWidget->addItem(strSetting.first);

    for (auto & intSetting : m_fileInterface.mainConfig().intSettings)
        ui->settingList_listWidget->addItem(intSetting.first);

    ui->basePath_lineEdit->setText(m_fileInterface.mainConfig().strSettings["Default base path"]);

    connect(ui->settingList_listWidget, &QListWidget::clicked, this, &MainWindow::settingClicked);
    connect(ui->settingAccept_pushButton, &QPushButton::clicked, this, &MainWindow::updateSelectedSetting);
    connect(ui->settingsSave_pushButton, &QPushButton::clicked, this, &MainWindow::saveSettingsToFile);
    connect(ui->settingsRestore_pushButton, &QPushButton::clicked, this, &MainWindow::restoreSettingsAll);
    connect(ui->settingRestore_pushButton, &QPushButton::clicked, this, &MainWindow::restoreSetting);
    connect(ui->settingSearch_lineEdit, &QLineEdit::textChanged, this, &MainWindow::searchForSetting);
}
