#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <atomic>

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

private slots:
    void addSelectedLibrary();
    void removeSelectedLibrary();

    void fillProjectList();
    void loadDependencyList(const QString & projectName);
    void saveChanges();

    void removeFiles();

    void searchForLibrary(const QString & changedText);
    void searchForProject(const QString & changedText);
    void searchForSetting(const QString &changedText);

    void changedMenu(QAction * menuAction);

    void build();
    void rebuild();

    void printInfo(const QString & what);

    void archiveComplete();
    void archive();
    void projectSelected();

    void buildComplete(const QString & projectName, const bool result);

    void recursiveDependencySearch();

    void settingClicked();
    void updateSelectedSetting();
    void saveSettingsToFile();
    void restoreSettingsAll();
    void restoreSetting();

private:
    Ui::MainWindow *ui;

    GraphWidget::DependencyGraphWidget * m_depGraphWidget;

    FileWork::ProjectDirectoryFileInterface m_fileInterface;

    FileWork::Cleaner m_cleaner;

    QString basePath;

    std::atomic<float> m_progressPercent;
    int projectsToBuild = 0;

    void updateProjectList();
    void setupAvailableLibrariesView();
    void setupSignals();
    void removeButtonFocuses();
    void setupSettings();

    void updateUsedLibraries();
};

#endif // MAINWINDOW_H
