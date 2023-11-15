#include "mainwindow.h"
#include "ui_mainwindow.h"

void MainWindow::build()
{
    if (!ui->projects_listWidget->count())
    {
        emit printInfo("Список проектов пуст, нечего собирать");
        return;
    }

    const int currentPercent = m_progressPercent.load();
    if ((currentPercent != 100) && (currentPercent != 0))
    {
        emit printInfo("Сборка уже ведётся. Проверьте прогресс в меню сборки");
        return;
    }

    emit updatePercent(0);

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

    const int currentPercent = m_progressPercent.load();
    if ((currentPercent != 100) && (currentPercent != 0))
    {
        emit printInfo("Сборка уже ведётся. Проверьте прогресс в меню сборки");
        return;
    }

    emit updatePercent(0);
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


void MainWindow::buildComplete(const QString &projectName, const bool result)
{
    if (result)
    {
        emit printInfo(QString("Собран проект %1").arg(projectName));
        emit updatePercent(m_progressPercent.load() + 100.0f / (float)projectsToBuild);
    }
    else
    {
        emit printInfo(QString("Ошибка сборки проекта %1. Более полная информация в файле %2").arg(projectName, m_fileInterface.mainConfig().strSettings["Log file name"]));
        emit updatePercent(100);
    }
}
