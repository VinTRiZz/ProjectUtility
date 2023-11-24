#include "mainwindow.h"
#include "ui_mainwindow.h"

// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// ------------------------------------ Remove files ------------------------------------ //
// -------------------------------------------------------------------------------------- //
void MainWindow::removeFiles()
{
    if (ui->projects_listWidget->count() == 0)
    {
        emit printInfo("Проекты не найдены, чистки не будет");
        return;
    }

    emit updatePercent(0);

    emit printInfo("Анализ директорий...");

    int filesToRemove = ProjectUtility::FILE_REMOVE_TYPE::NO_FILE;

    if (ui->bin_checkBox->isChecked())
        filesToRemove |= ProjectUtility::FILE_REMOVE_TYPE::BIN;

    if (ui->build_checkBox->isChecked())
        filesToRemove |= ProjectUtility::FILE_REMOVE_TYPE::BUILD;

    if (ui->lib_checkBox->isChecked())
        filesToRemove |= ProjectUtility::FILE_REMOVE_TYPE::LIB;

    if (ui->makeFiles_checkBox->isChecked())
        filesToRemove |= ProjectUtility::FILE_REMOVE_TYPE::MAKEFILE;

    if (ui->qmakeStash_checkBox->isChecked())
        filesToRemove |= ProjectUtility::FILE_REMOVE_TYPE::QMAKE_STASH;

    QStringList fileList = m_cleaner->getFileList(m_fileInterface.currentDirectory(), filesToRemove);
    emit updatePercent(33);

    emit printInfo("Очистка от ошибок, если имеются...");
    m_cleaner->clearFromMistakes(fileList);
    emit updatePercent(66);

    emit printInfo("Удаление...");
    m_cleaner->removeFiles(fileList);
    emit printInfo("Файлы удалены");
    emit updatePercent(100);
}

void MainWindow::generateProject()
{
    if (!m_fileInterface.configuration().strSettings["Default main template path"].isEmpty())
    {
        if (QMessageBox::warning(
                    this, "Внимание",
                    QString("Проект будет сконфигурирован так, что\nу него будет указано использование\n[  %1  ]\nв качестве общего шаблона. Продолжить?").arg(m_fileInterface.configuration().strSettings["Default main template path"]),
                    QMessageBox::Yes, QMessageBox::No
            ) == QMessageBox::No)
        {
            emit printInfo("Генерация отменена");
            return;
        }
    }

    ProjectUtility::ProjectBaseConfiguration config;

    config.projectName = ui->projectName_lineEdit->text();
    config.baseDir = ui->projectPath_lineEdit->text();

    QFileInfo dirTester(config.baseDir);
    if (config.baseDir.isEmpty() || !dirTester.exists() || !dirTester.isDir())
    {
        emit printInfo("Ошибка: путь до директории, в которой нужно создать проект, пустой или неверный. Проект не создан");
        return;
    }

    config.hasDeps = ui->hasDeps_checkBox->isChecked();
    config.isLibrary = ui->generateLib_checkBox->isChecked();
    config.hasGui = ui->hasGui_checkBox->isChecked();
    config.hasBuildPri = ui->hasBuildPri_checkBox->isChecked();

    if (m_fileInterface.generateProject(config))
        emit printInfo(QString("Проект создан по пути:\n %1").arg(config.baseDir));
    else
        emit printInfo("Ошибка создания проекта! Проверьте введённые данные");
}

void MainWindow::log(const QVariant &what)
{
    if (ui->log_plainTextEdit->toPlainText().size() < m_fileInterface.configuration().intSettings["Maximum log size in symbols"])
        ui->log_plainTextEdit->appendPlainText(what.toString());
    else
    {
        ui->notifications_listWidget->clear();
        ui->log_plainTextEdit->clear();
    }
}


// -------------------------------------------------------------------------------------- //
// -------------------------------------------------------------------------------------- //
// ----------------------------------- Archive files ------------------------------------ //
// -------------------------------------------------------------------------------------- //
void MainWindow::archiveComplete(bool result)
{
    if (result)
        emit printInfo("Архив создан");
    else
        emit printInfo("Ошибка создания архива");
}

void MainWindow::archive()
{
    QString archivePath = ui->archivePath_lineEdit->text();
    if (archivePath[0] == '.')
    {
        archivePath.remove(0, 1);
        archivePath = m_fileInterface.configuration().strSettings["Program default directory"] + "/" + archivePath;
    } else if (archivePath[0] != '/')
    {
        archivePath = m_fileInterface.configuration().strSettings["Program default directory"] + "/" + archivePath;
    }

    if (!archivePath.contains(".zip"))
        archivePath += ".zip";

    if (ui->archiveAll_radioButton->isChecked())
    {

        m_fileInterface.archiveAllProjects(archivePath);

    } else if (ui->archiveSelected_radioButton->isChecked())
    {
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

        const QString projectName = pItem->text();

        m_fileInterface.archiveProject(projectName, archivePath);
    }

    emit printInfo("Архивация запущена");
}
