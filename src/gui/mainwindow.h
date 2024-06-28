#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QMessageBox>
#include <QFileInfo>
#include <QThread>
#include <QValidator>

#include <atomic>
#include <QDebug>

#include "components/projectdirectoryfileinterface.h"
#include "components/cleaner.h"
#include "components/projectbasegenerator.h"
#include "components/taskmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    void setBasePath(const QString & basePath);
    void init();

private slots:
    // Window actions
    void changedMenu(QAction * menuAction);
    void printInfo(const QString & what);
    void reloadGraph();
    void updatePercent(float newValue);

    // Data edit
    void addSelectedLibrary();
    void removeSelectedLibrary();

    // Data save/load
    void fillProjectList();
    void loadDependencyList(const QString & projectName);
    void saveChanges();

    // Searching
    void searchForLibrary(const QString & changedText);
    void searchForProject(const QString & changedText);
    void searchForSetting(const QString &changedText);
    void recursiveDependencySearch();

    // Building
    void build();
    void rebuild();
    void buildComplete(const QString & projectName, const bool result);

    // Archiving
    void archiveComplete(bool result);
    void archive();
    void projectSelected();

    // Etc
    void removeFiles();
    void generateProject();
    void log(const QVariant & what);

    // Settings
    void settingClicked();
    void updateSelectedSetting();
    void saveSettingsToFile();
    void restoreSettingsAll();
    void restoreSetting();

private:
    Ui::MainWindow *ui;

    ProjectUtility::ProjectDirectoryFileInterface m_fileInterface;
    GraphWidget::DependencyGraphWidget * m_depGraphWidget;
    ProjectUtility::Cleaner * m_cleaner;
    TaskManager m_taskManager;
    std::shared_ptr<TreeProxy::TreeItemModel> pTaskModel {};

    QString basePath;

    std::atomic<float> m_progressPercent;
    int projectsToBuild = 0;

    void updateProjectList();
    void setupAvailableLibrariesView();
    void setupSignals();
    void removeButtonFocuses();
    void setupSettings();
    void setupTaskModel();
    void saveTasks();
    void loadTasks();

    void updateUsedLibraries();
};

#endif // MAINWINDOW_H
