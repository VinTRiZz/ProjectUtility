#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "filework/projectdirectoryfileinterface.h"
#include "filework/cleaner.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void addSelectedLibrary();
    void removeSelectedLibrary();
    void loadDependencyList();

    void createBackup();
    void loadBackup();

    void setBasePath();

    void removeFiles();

private:
    Ui::MainWindow *ui;

    FileWork::ProjectDirectoryFileInterface m_fileInterface;

    FileWork::Cleaner m_cleaner;

    QString basePath;

    void updateProjectList();
    void setupAvailableLibrariesView();
    void updateUsedLibraries();
};

#endif // MAINWINDOW_H
