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

    emit printInfo("Анализ директорий...");

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

    emit printInfo("Очистка от ошибок, если имеются...");

    m_cleaner.clearFromMistakes(fileList);

    emit printInfo("Удаление...");

    m_cleaner.removeFiles(fileList);
    emit printInfo("Файлы удалены");
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
    if (ui->archiveAll_radioButton->isChecked())
    {
        const QString archivePath = ui->archivePath_lineEdit->text();

        m_fileInterface.archiveAllProjects(archivePath);

    } else if (ui->archiveSelected_radioButton->isChecked())
    {
        const QString archivePath = ui->archivePath_lineEdit->text();

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

        const QString archivePath = ui->archivePath_lineEdit->text();
        const QString projectName = pItem->text();

        m_fileInterface.archiveProject(projectName, archivePath);
    }

    emit printInfo("Архивация запущена");
}
