/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QCheckBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QListWidget>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QScrollArea>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *projectControl_action;
    QAction *depends_action;
    QAction *action;
    QAction *action_2;
    QAction *action_3;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QRadioButton *libs_radioButton;
    QRadioButton *apps_radioButton;
    QSpacerItem *horizontalSpacer;
    QLabel *label_9;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *basePath_lineEdit;
    QPushButton *update_pushButton;
    QLabel *label;
    QListWidget *projects_listWidget;
    QLineEdit *searchProject_lineEdit;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *cleanOutput_pushButton;
    QStackedWidget *menu_stackedWidget;
    QWidget *deps_page;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QListWidget *avaliableLibs_listWidget;
    QLineEdit *search_lineEdit;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_pushButton;
    QPushButton *remove_pushButton;
    QPushButton *saveChanges_pushButton;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *addedLibs_listWidget;
    QLineEdit *recursiveSearch_lineEdit;
    QPushButton *reloadGraph_pushButton;
    QSpacerItem *verticalSpacer_4;
    QScrollArea *graph_scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *misc_page;
    QGridLayout *gridLayout_2;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *horizontalSpacer_3;
    QVBoxLayout *verticalLayout_9;
    QHBoxLayout *horizontalLayout;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_8;
    QLabel *label_8;
    QRadioButton *debugTarget_radioButton;
    QRadioButton *releaseTarget_radioButton;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_11;
    QLabel *label_7;
    QRadioButton *buildAll_radioButton;
    QRadioButton *buildCurrent_radioButton;
    QVBoxLayout *verticalLayout_4;
    QPushButton *build_pushButton;
    QPushButton *rebuild_pushButton;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QCheckBox *makeFiles_checkBox;
    QCheckBox *qmakeStash_checkBox;
    QCheckBox *lib_checkBox;
    QCheckBox *bin_checkBox;
    QCheckBox *build_checkBox;
    QPushButton *clean_pushButton;
    QSpacerItem *verticalSpacer;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_6;
    QRadioButton *archiveAll_radioButton;
    QRadioButton *archiveSelected_radioButton;
    QRadioButton *archiveCurrent_radioButton;
    QCheckBox *autoName_checkBox;
    QLineEdit *archivePath_lineEdit;
    QPushButton *archive_pushButton;
    QProgressBar *progressBar;
    QWidget *templateCreate_page;
    QGridLayout *gridLayout_5;
    QVBoxLayout *verticalLayout_17;
    QWidget *widget_7;
    QVBoxLayout *verticalLayout_16;
    QLabel *label_13;
    QCheckBox *generateLib_checkBox;
    QLineEdit *projectName_lineEdit;
    QLineEdit *projectPath_lineEdit;
    QPushButton *generateProject_pushButton;
    QSpacerItem *verticalSpacer_7;
    QSpacerItem *horizontalSpacer_4;
    QVBoxLayout *verticalLayout_18;
    QLabel *label_14;
    QWidget *widget_8;
    QCheckBox *hasDeps_checkBox;
    QCheckBox *hasBuildPri_checkBox;
    QCheckBox *hasGui_checkBox;
    QSpacerItem *verticalSpacer_6;
    QSpacerItem *verticalSpacer_5;
    QWidget *settings_page;
    QGridLayout *gridLayout_3;
    QWidget *widget_6;
    QGridLayout *gridLayout_4;
    QListWidget *settingList_listWidget;
    QLabel *label_16;
    QSpacerItem *verticalSpacer_3;
    QLineEdit *settingSearch_lineEdit;
    QVBoxLayout *verticalLayout_15;
    QLabel *label_15;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_13;
    QLabel *label_10;
    QLabel *label_11;
    QLabel *label_12;
    QVBoxLayout *verticalLayout_14;
    QLabel *settingName_label;
    QLabel *settingValue_label;
    QLineEdit *settingValue_lineEdit;
    QPushButton *settingAccept_pushButton;
    QPushButton *settingRestore_pushButton;
    QPushButton *settingsRestore_pushButton;
    QPushButton *settingsSave_pushButton;
    QSpacerItem *horizontalSpacer_5;
    QListWidget *notifications_listWidget;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(800, 600);
        MainWindow->setMinimumSize(QSize(800, 600));
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        MainWindow->setStyleSheet(QLatin1String("QWidget\n"
"{\n"
"color: rgb(186, 186, 186);\n"
"background-color: rgb(58, 58, 58);\n"
"}\n"
"\n"
"QWidget:selected\n"
"{\n"
"background-color: rgb(185, 185, 185);\n"
"color: rgb(41, 41, 41);\n"
"}\n"
"\n"
"QMenu:hover\n"
"{\n"
"background-color: rgb(185, 185, 185);\n"
"color: rgb(41, 41, 41);\n"
"}\n"
"\n"
"QPushButton \n"
"{\n"
"	background-color: rgb(58, 58, 58);\n"
"	color: rgb(242, 242, 242);\n"
"}\n"
"\n"
"QPushButton:clicked\n"
"{\n"
"background-color: rgb(10, 70, 6);\n"
"	color: rgb(242, 242, 242);\n"
"}\n"
"\n"
"QPushButton:hover\n"
"{\n"
"	background-color: rgb(172, 172, 172);\n"
"	color: rgb(24, 24, 24);\n"
"}\n"
"\n"
"QLabel\n"
"{\n"
"	padding: 2px;\n"
"	background-color: rgb(52, 52, 52); \n"
"	color: rgb(193, 198, 110);\n"
"	border-width: 1px;\n"
"	border-style: solid;\n"
"	border-color: rgb(186, 186, 186);\n"
"}\n"
"\n"
"QRadioButton\n"
"{\n"
"	background-color: rgb(58, 58, 58);\n"
"	color: rgb(242, 242, 242);\n"
"	border-radius:  3;\n"
"}\n"
"\n"
"QRadioButton:hover\n"
"{\n"
"	background-color: "
                        "rgb(146, 146, 146);\n"
"	color: rgb(26, 26, 26);\n"
"	border-radius:  3;\n"
"}\n"
"\n"
"QRadioButton:checked\n"
"{\n"
"	background-color: rgb(113, 108, 10);\n"
"	color: rgb(30, 30, 30);\n"
"	border-radius:  9;	\n"
"}\n"
"\n"
"QCheckBox\n"
"{\n"
"	background-color: rgb(58, 58, 58);\n"
"	color: rgb(242, 242, 242);\n"
"	border-radius:  3;\n"
"}\n"
"\n"
"QCheckBox:hover\n"
"{\n"
"	\n"
"	background-color: rgb(146, 146, 146);\n"
"	color: rgb(26, 26, 26);\n"
"	border-radius:  3;\n"
"}\n"
"\n"
"QCheckBox:checked\n"
"{\n"
"	background-color: rgb(113, 108, 10);\n"
"	color: rgb(30, 30, 30);\n"
"	border-radius:  9;\n"
"}\n"
"\n"
"QLineEdit\n"
"{\n"
"background-color: rgb(58, 58, 58);\n"
"color: rgb(122, 198, 255);\n"
"}\n"
"\n"
"QLineEdit:hover\n"
"{\n"
"background-color: rgb(77, 77, 77);\n"
"color: rgb(122, 198, 255);\n"
"}\n"
"\n"
"QListWidget\n"
"{\n"
"background-color: rgb(58, 58, 58);\n"
"	color: rgb(221, 221, 221);\n"
"}\n"
"\n"
"QListWidget:item:selected\n"
"{\n"
"	background-color: rgb(179, 174, 78);\n"
"	color: r"
                        "gb(48, 48, 48);\n"
"}\n"
"\n"
"QListWidget:item:hover\n"
"{\n"
"	background-color: rgb(144, 144, 144);\n"
"	color: rgb(48, 48, 48);\n"
"}"));
        projectControl_action = new QAction(MainWindow);
        projectControl_action->setObjectName(QStringLiteral("projectControl_action"));
        depends_action = new QAction(MainWindow);
        depends_action->setObjectName(QStringLiteral("depends_action"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        action_2 = new QAction(MainWindow);
        action_2->setObjectName(QStringLiteral("action_2"));
        action_3 = new QAction(MainWindow);
        action_3->setObjectName(QStringLiteral("action_3"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy);
        widget->setStyleSheet(QStringLiteral(""));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy1);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_5->addWidget(label_5);

        libs_radioButton = new QRadioButton(widget);
        libs_radioButton->setObjectName(QStringLiteral("libs_radioButton"));
        libs_radioButton->setStyleSheet(QStringLiteral(""));
        libs_radioButton->setChecked(true);

        verticalLayout_5->addWidget(libs_radioButton);

        apps_radioButton = new QRadioButton(widget);
        apps_radioButton->setObjectName(QStringLiteral("apps_radioButton"));
        apps_radioButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_5->addWidget(apps_radioButton);


        gridLayout->addWidget(widget, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 2, 0, 1, 3);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        basePath_lineEdit = new QLineEdit(centralWidget);
        basePath_lineEdit->setObjectName(QStringLiteral("basePath_lineEdit"));
        sizePolicy1.setHeightForWidth(basePath_lineEdit->sizePolicy().hasHeightForWidth());
        basePath_lineEdit->setSizePolicy(sizePolicy1);
        basePath_lineEdit->setMaximumSize(QSize(350, 16777215));
        basePath_lineEdit->setFocusPolicy(Qt::ClickFocus);
        basePath_lineEdit->setStyleSheet(QStringLiteral("color: rgb(167, 167, 167);"));
        basePath_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_10->addWidget(basePath_lineEdit);


        verticalLayout_7->addLayout(verticalLayout_10);

        update_pushButton = new QPushButton(centralWidget);
        update_pushButton->setObjectName(QStringLiteral("update_pushButton"));
        sizePolicy1.setHeightForWidth(update_pushButton->sizePolicy().hasHeightForWidth());
        update_pushButton->setSizePolicy(sizePolicy1);
        update_pushButton->setMinimumSize(QSize(0, 0));
        update_pushButton->setMaximumSize(QSize(500, 16777215));
        update_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_7->addWidget(update_pushButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy1.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy1);
        label->setMaximumSize(QSize(500, 16777215));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label);

        projects_listWidget = new QListWidget(centralWidget);
        projects_listWidget->setObjectName(QStringLiteral("projects_listWidget"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(projects_listWidget->sizePolicy().hasHeightForWidth());
        projects_listWidget->setSizePolicy(sizePolicy2);
        projects_listWidget->setMaximumSize(QSize(500, 16777215));
        projects_listWidget->setFocusPolicy(Qt::NoFocus);
        projects_listWidget->setStyleSheet(QStringLiteral(""));
        projects_listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        projects_listWidget->setSortingEnabled(true);

        verticalLayout_7->addWidget(projects_listWidget);

        searchProject_lineEdit = new QLineEdit(centralWidget);
        searchProject_lineEdit->setObjectName(QStringLiteral("searchProject_lineEdit"));
        sizePolicy.setHeightForWidth(searchProject_lineEdit->sizePolicy().hasHeightForWidth());
        searchProject_lineEdit->setSizePolicy(sizePolicy);
        searchProject_lineEdit->setMaximumSize(QSize(500, 16777215));
        searchProject_lineEdit->setFocusPolicy(Qt::ClickFocus);
        searchProject_lineEdit->setStyleSheet(QStringLiteral(""));
        searchProject_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(searchProject_lineEdit);


        gridLayout->addLayout(verticalLayout_7, 1, 0, 1, 3);

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        cleanOutput_pushButton = new QPushButton(centralWidget);
        cleanOutput_pushButton->setObjectName(QStringLiteral("cleanOutput_pushButton"));

        gridLayout->addWidget(cleanOutput_pushButton, 4, 0, 1, 3);

        menu_stackedWidget = new QStackedWidget(centralWidget);
        menu_stackedWidget->setObjectName(QStringLiteral("menu_stackedWidget"));
        deps_page = new QWidget();
        deps_page->setObjectName(QStringLiteral("deps_page"));
        horizontalLayout_4 = new QHBoxLayout(deps_page);
        horizontalLayout_4->setSpacing(3);
        horizontalLayout_4->setContentsMargins(11, 11, 11, 11);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalLayout_4->setContentsMargins(0, 0, 0, 0);
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(deps_page);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy1.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy1);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        avaliableLibs_listWidget = new QListWidget(deps_page);
        avaliableLibs_listWidget->setObjectName(QStringLiteral("avaliableLibs_listWidget"));
        sizePolicy.setHeightForWidth(avaliableLibs_listWidget->sizePolicy().hasHeightForWidth());
        avaliableLibs_listWidget->setSizePolicy(sizePolicy);

        verticalLayout->addWidget(avaliableLibs_listWidget);

        search_lineEdit = new QLineEdit(deps_page);
        search_lineEdit->setObjectName(QStringLiteral("search_lineEdit"));
        sizePolicy1.setHeightForWidth(search_lineEdit->sizePolicy().hasHeightForWidth());
        search_lineEdit->setSizePolicy(sizePolicy1);
        search_lineEdit->setFocusPolicy(Qt::ClickFocus);
        search_lineEdit->setStyleSheet(QStringLiteral(""));
        search_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(search_lineEdit);


        verticalLayout_6->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        add_pushButton = new QPushButton(deps_page);
        add_pushButton->setObjectName(QStringLiteral("add_pushButton"));
        sizePolicy1.setHeightForWidth(add_pushButton->sizePolicy().hasHeightForWidth());
        add_pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(add_pushButton);

        remove_pushButton = new QPushButton(deps_page);
        remove_pushButton->setObjectName(QStringLiteral("remove_pushButton"));
        sizePolicy1.setHeightForWidth(remove_pushButton->sizePolicy().hasHeightForWidth());
        remove_pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(remove_pushButton);

        saveChanges_pushButton = new QPushButton(deps_page);
        saveChanges_pushButton->setObjectName(QStringLiteral("saveChanges_pushButton"));
        sizePolicy1.setHeightForWidth(saveChanges_pushButton->sizePolicy().hasHeightForWidth());
        saveChanges_pushButton->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(saveChanges_pushButton);


        verticalLayout_6->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(deps_page);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy1.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy1);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        addedLibs_listWidget = new QListWidget(deps_page);
        addedLibs_listWidget->setObjectName(QStringLiteral("addedLibs_listWidget"));
        sizePolicy.setHeightForWidth(addedLibs_listWidget->sizePolicy().hasHeightForWidth());
        addedLibs_listWidget->setSizePolicy(sizePolicy);

        verticalLayout_2->addWidget(addedLibs_listWidget);


        verticalLayout_6->addLayout(verticalLayout_2);

        recursiveSearch_lineEdit = new QLineEdit(deps_page);
        recursiveSearch_lineEdit->setObjectName(QStringLiteral("recursiveSearch_lineEdit"));
        sizePolicy1.setHeightForWidth(recursiveSearch_lineEdit->sizePolicy().hasHeightForWidth());
        recursiveSearch_lineEdit->setSizePolicy(sizePolicy1);
        recursiveSearch_lineEdit->setFocusPolicy(Qt::ClickFocus);
        recursiveSearch_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_6->addWidget(recursiveSearch_lineEdit);

        reloadGraph_pushButton = new QPushButton(deps_page);
        reloadGraph_pushButton->setObjectName(QStringLiteral("reloadGraph_pushButton"));

        verticalLayout_6->addWidget(reloadGraph_pushButton);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_4->addLayout(verticalLayout_6);

        graph_scrollArea = new QScrollArea(deps_page);
        graph_scrollArea->setObjectName(QStringLiteral("graph_scrollArea"));
        QSizePolicy sizePolicy3(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(graph_scrollArea->sizePolicy().hasHeightForWidth());
        graph_scrollArea->setSizePolicy(sizePolicy3);
        graph_scrollArea->viewport()->setProperty("cursor", QVariant(QCursor(Qt::ArrowCursor)));
        graph_scrollArea->setMouseTracking(false);
        graph_scrollArea->setSizeAdjustPolicy(QAbstractScrollArea::AdjustIgnored);
        graph_scrollArea->setWidgetResizable(true);
        graph_scrollArea->setAlignment(Qt::AlignBottom|Qt::AlignHCenter);
        scrollAreaWidgetContents = new QWidget();
        scrollAreaWidgetContents->setObjectName(QStringLiteral("scrollAreaWidgetContents"));
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 330, 534));
        graph_scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_4->addWidget(graph_scrollArea);

        menu_stackedWidget->addWidget(deps_page);
        misc_page = new QWidget();
        misc_page->setObjectName(QStringLiteral("misc_page"));
        gridLayout_2 = new QGridLayout(misc_page);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_3 = new QWidget(misc_page);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        widget_3->setStyleSheet(QStringLiteral(""));
        verticalLayout_8 = new QVBoxLayout(widget_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_8 = new QLabel(widget_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy1.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy1);
        label_8->setStyleSheet(QStringLiteral(""));
        label_8->setAlignment(Qt::AlignCenter);

        verticalLayout_8->addWidget(label_8);

        debugTarget_radioButton = new QRadioButton(widget_3);
        debugTarget_radioButton->setObjectName(QStringLiteral("debugTarget_radioButton"));
        debugTarget_radioButton->setStyleSheet(QStringLiteral(""));
        debugTarget_radioButton->setChecked(true);

        verticalLayout_8->addWidget(debugTarget_radioButton);

        releaseTarget_radioButton = new QRadioButton(widget_3);
        releaseTarget_radioButton->setObjectName(QStringLiteral("releaseTarget_radioButton"));
        releaseTarget_radioButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_8->addWidget(releaseTarget_radioButton);


        horizontalLayout->addWidget(widget_3);

        widget_2 = new QWidget(misc_page);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        widget_2->setStyleSheet(QStringLiteral(""));
        verticalLayout_11 = new QVBoxLayout(widget_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy1.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy1);
        label_7->setStyleSheet(QStringLiteral(""));
        label_7->setAlignment(Qt::AlignCenter);

        verticalLayout_11->addWidget(label_7);

        buildAll_radioButton = new QRadioButton(widget_2);
        buildAll_radioButton->setObjectName(QStringLiteral("buildAll_radioButton"));
        buildAll_radioButton->setStyleSheet(QStringLiteral(""));
        buildAll_radioButton->setChecked(false);

        verticalLayout_11->addWidget(buildAll_radioButton);

        buildCurrent_radioButton = new QRadioButton(widget_2);
        buildCurrent_radioButton->setObjectName(QStringLiteral("buildCurrent_radioButton"));
        buildCurrent_radioButton->setStyleSheet(QStringLiteral(""));
        buildCurrent_radioButton->setChecked(true);

        verticalLayout_11->addWidget(buildCurrent_radioButton);


        horizontalLayout->addWidget(widget_2);


        verticalLayout_9->addLayout(horizontalLayout);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(2);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        build_pushButton = new QPushButton(misc_page);
        build_pushButton->setObjectName(QStringLiteral("build_pushButton"));
        build_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(build_pushButton);

        rebuild_pushButton = new QPushButton(misc_page);
        rebuild_pushButton->setObjectName(QStringLiteral("rebuild_pushButton"));
        rebuild_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(rebuild_pushButton);


        verticalLayout_9->addLayout(verticalLayout_4);


        gridLayout_2->addLayout(verticalLayout_9, 0, 0, 1, 1);

        widget_5 = new QWidget(misc_page);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy1.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy1);
        label_4->setStyleSheet(QStringLiteral(""));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        makeFiles_checkBox = new QCheckBox(widget_5);
        makeFiles_checkBox->setObjectName(QStringLiteral("makeFiles_checkBox"));
        makeFiles_checkBox->setFocusPolicy(Qt::NoFocus);
        makeFiles_checkBox->setStyleSheet(QStringLiteral(""));
        makeFiles_checkBox->setChecked(true);

        verticalLayout_3->addWidget(makeFiles_checkBox);

        qmakeStash_checkBox = new QCheckBox(widget_5);
        qmakeStash_checkBox->setObjectName(QStringLiteral("qmakeStash_checkBox"));
        qmakeStash_checkBox->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(qmakeStash_checkBox);

        lib_checkBox = new QCheckBox(widget_5);
        lib_checkBox->setObjectName(QStringLiteral("lib_checkBox"));
        lib_checkBox->setFocusPolicy(Qt::NoFocus);
        lib_checkBox->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(lib_checkBox);

        bin_checkBox = new QCheckBox(widget_5);
        bin_checkBox->setObjectName(QStringLiteral("bin_checkBox"));
        bin_checkBox->setFocusPolicy(Qt::NoFocus);
        bin_checkBox->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(bin_checkBox);

        build_checkBox = new QCheckBox(widget_5);
        build_checkBox->setObjectName(QStringLiteral("build_checkBox"));
        build_checkBox->setFocusPolicy(Qt::NoFocus);
        build_checkBox->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(build_checkBox);

        clean_pushButton = new QPushButton(widget_5);
        clean_pushButton->setObjectName(QStringLiteral("clean_pushButton"));
        clean_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_3->addWidget(clean_pushButton);


        gridLayout_2->addWidget(widget_5, 0, 1, 1, 1);

        verticalSpacer = new QSpacerItem(119, 431, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 2, 1);

        widget_4 = new QWidget(misc_page);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        sizePolicy.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy);
        widget_4->setStyleSheet(QStringLiteral(""));
        verticalLayout_12 = new QVBoxLayout(widget_4);
        verticalLayout_12->setSpacing(2);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(2, 2, 2, 2);
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy1.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy1);
        label_6->setStyleSheet(QStringLiteral(""));
        label_6->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(label_6);

        archiveAll_radioButton = new QRadioButton(widget_4);
        archiveAll_radioButton->setObjectName(QStringLiteral("archiveAll_radioButton"));
        archiveAll_radioButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_12->addWidget(archiveAll_radioButton);

        archiveSelected_radioButton = new QRadioButton(widget_4);
        archiveSelected_radioButton->setObjectName(QStringLiteral("archiveSelected_radioButton"));
        archiveSelected_radioButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_12->addWidget(archiveSelected_radioButton);

        archiveCurrent_radioButton = new QRadioButton(widget_4);
        archiveCurrent_radioButton->setObjectName(QStringLiteral("archiveCurrent_radioButton"));
        archiveCurrent_radioButton->setStyleSheet(QLatin1String("border-width: 0px;\n"
"border-style: solid;\n"
"border-color: rgb(186, 186, 186);"));
        archiveCurrent_radioButton->setChecked(true);

        verticalLayout_12->addWidget(archiveCurrent_radioButton);

        autoName_checkBox = new QCheckBox(widget_4);
        autoName_checkBox->setObjectName(QStringLiteral("autoName_checkBox"));
        autoName_checkBox->setStyleSheet(QStringLiteral(""));

        verticalLayout_12->addWidget(autoName_checkBox);

        archivePath_lineEdit = new QLineEdit(widget_4);
        archivePath_lineEdit->setObjectName(QStringLiteral("archivePath_lineEdit"));
        sizePolicy1.setHeightForWidth(archivePath_lineEdit->sizePolicy().hasHeightForWidth());
        archivePath_lineEdit->setSizePolicy(sizePolicy1);
        archivePath_lineEdit->setFocusPolicy(Qt::ClickFocus);
        archivePath_lineEdit->setStyleSheet(QStringLiteral("color: rgb(215, 215, 215);"));
        archivePath_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(archivePath_lineEdit);

        archive_pushButton = new QPushButton(widget_4);
        archive_pushButton->setObjectName(QStringLiteral("archive_pushButton"));
        archive_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_12->addWidget(archive_pushButton);


        gridLayout_2->addWidget(widget_4, 1, 0, 1, 1);

        progressBar = new QProgressBar(misc_page);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        sizePolicy1.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy1);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progressBar->setOrientation(Qt::Horizontal);

        gridLayout_2->addWidget(progressBar, 3, 0, 1, 3);

        menu_stackedWidget->addWidget(misc_page);
        templateCreate_page = new QWidget();
        templateCreate_page->setObjectName(QStringLiteral("templateCreate_page"));
        gridLayout_5 = new QGridLayout(templateCreate_page);
        gridLayout_5->setSpacing(6);
        gridLayout_5->setContentsMargins(11, 11, 11, 11);
        gridLayout_5->setObjectName(QStringLiteral("gridLayout_5"));
        verticalLayout_17 = new QVBoxLayout();
        verticalLayout_17->setSpacing(6);
        verticalLayout_17->setObjectName(QStringLiteral("verticalLayout_17"));
        widget_7 = new QWidget(templateCreate_page);
        widget_7->setObjectName(QStringLiteral("widget_7"));
        verticalLayout_16 = new QVBoxLayout(widget_7);
        verticalLayout_16->setSpacing(6);
        verticalLayout_16->setContentsMargins(11, 11, 11, 11);
        verticalLayout_16->setObjectName(QStringLiteral("verticalLayout_16"));
        label_13 = new QLabel(widget_7);
        label_13->setObjectName(QStringLiteral("label_13"));
        label_13->setAlignment(Qt::AlignCenter);

        verticalLayout_16->addWidget(label_13);

        generateLib_checkBox = new QCheckBox(widget_7);
        generateLib_checkBox->setObjectName(QStringLiteral("generateLib_checkBox"));
        generateLib_checkBox->setChecked(true);

        verticalLayout_16->addWidget(generateLib_checkBox);


        verticalLayout_17->addWidget(widget_7);

        projectName_lineEdit = new QLineEdit(templateCreate_page);
        projectName_lineEdit->setObjectName(QStringLiteral("projectName_lineEdit"));
        sizePolicy1.setHeightForWidth(projectName_lineEdit->sizePolicy().hasHeightForWidth());
        projectName_lineEdit->setSizePolicy(sizePolicy1);
        projectName_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(projectName_lineEdit);

        projectPath_lineEdit = new QLineEdit(templateCreate_page);
        projectPath_lineEdit->setObjectName(QStringLiteral("projectPath_lineEdit"));
        sizePolicy1.setHeightForWidth(projectPath_lineEdit->sizePolicy().hasHeightForWidth());
        projectPath_lineEdit->setSizePolicy(sizePolicy1);
        projectPath_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_17->addWidget(projectPath_lineEdit);

        generateProject_pushButton = new QPushButton(templateCreate_page);
        generateProject_pushButton->setObjectName(QStringLiteral("generateProject_pushButton"));
        sizePolicy1.setHeightForWidth(generateProject_pushButton->sizePolicy().hasHeightForWidth());
        generateProject_pushButton->setSizePolicy(sizePolicy1);

        verticalLayout_17->addWidget(generateProject_pushButton);

        verticalSpacer_7 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_17->addItem(verticalSpacer_7);


        gridLayout_5->addLayout(verticalLayout_17, 0, 0, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(354, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_5->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        verticalLayout_18 = new QVBoxLayout();
        verticalLayout_18->setSpacing(6);
        verticalLayout_18->setObjectName(QStringLiteral("verticalLayout_18"));
        label_14 = new QLabel(templateCreate_page);
        label_14->setObjectName(QStringLiteral("label_14"));
        label_14->setAlignment(Qt::AlignCenter);

        verticalLayout_18->addWidget(label_14);

        widget_8 = new QWidget(templateCreate_page);
        widget_8->setObjectName(QStringLiteral("widget_8"));
        sizePolicy2.setHeightForWidth(widget_8->sizePolicy().hasHeightForWidth());
        widget_8->setSizePolicy(sizePolicy2);
        hasDeps_checkBox = new QCheckBox(widget_8);
        hasDeps_checkBox->setObjectName(QStringLiteral("hasDeps_checkBox"));
        hasDeps_checkBox->setGeometry(QRect(9, 9, 69, 19));
        hasBuildPri_checkBox = new QCheckBox(widget_8);
        hasBuildPri_checkBox->setObjectName(QStringLiteral("hasBuildPri_checkBox"));
        hasBuildPri_checkBox->setGeometry(QRect(9, 34, 70, 19));
        hasGui_checkBox = new QCheckBox(widget_8);
        hasGui_checkBox->setObjectName(QStringLiteral("hasGui_checkBox"));
        hasGui_checkBox->setGeometry(QRect(9, 59, 44, 19));

        verticalLayout_18->addWidget(widget_8);

        verticalSpacer_6 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_18->addItem(verticalSpacer_6);


        gridLayout_5->addLayout(verticalLayout_18, 0, 1, 1, 1);

        verticalSpacer_5 = new QSpacerItem(20, 393, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_5->addItem(verticalSpacer_5, 1, 0, 1, 2);

        menu_stackedWidget->addWidget(templateCreate_page);
        settings_page = new QWidget();
        settings_page->setObjectName(QStringLiteral("settings_page"));
        gridLayout_3 = new QGridLayout(settings_page);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        widget_6 = new QWidget(settings_page);
        widget_6->setObjectName(QStringLiteral("widget_6"));
        gridLayout_4 = new QGridLayout(widget_6);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QStringLiteral("gridLayout_4"));
        settingList_listWidget = new QListWidget(widget_6);
        settingList_listWidget->setObjectName(QStringLiteral("settingList_listWidget"));
        settingList_listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        settingList_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        settingList_listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        settingList_listWidget->setSortingEnabled(true);

        gridLayout_4->addWidget(settingList_listWidget, 1, 0, 4, 1);

        label_16 = new QLabel(widget_6);
        label_16->setObjectName(QStringLiteral("label_16"));
        label_16->setMaximumSize(QSize(16777215, 50));
        label_16->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(label_16, 0, 0, 1, 1);

        verticalSpacer_3 = new QSpacerItem(20, 324, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_4->addItem(verticalSpacer_3, 4, 1, 1, 1);

        settingSearch_lineEdit = new QLineEdit(widget_6);
        settingSearch_lineEdit->setObjectName(QStringLiteral("settingSearch_lineEdit"));
        settingSearch_lineEdit->setFocusPolicy(Qt::ClickFocus);
        settingSearch_lineEdit->setAlignment(Qt::AlignCenter);

        gridLayout_4->addWidget(settingSearch_lineEdit, 5, 0, 1, 1);

        verticalLayout_15 = new QVBoxLayout();
        verticalLayout_15->setSpacing(6);
        verticalLayout_15->setObjectName(QStringLiteral("verticalLayout_15"));
        label_15 = new QLabel(widget_6);
        label_15->setObjectName(QStringLiteral("label_15"));
        label_15->setAlignment(Qt::AlignCenter);

        verticalLayout_15->addWidget(label_15);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        verticalLayout_13 = new QVBoxLayout();
        verticalLayout_13->setSpacing(6);
        verticalLayout_13->setObjectName(QStringLiteral("verticalLayout_13"));
        label_10 = new QLabel(widget_6);
        label_10->setObjectName(QStringLiteral("label_10"));
        label_10->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_10);

        label_11 = new QLabel(widget_6);
        label_11->setObjectName(QStringLiteral("label_11"));
        label_11->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_11);

        label_12 = new QLabel(widget_6);
        label_12->setObjectName(QStringLiteral("label_12"));
        label_12->setAlignment(Qt::AlignCenter);

        verticalLayout_13->addWidget(label_12);


        horizontalLayout_3->addLayout(verticalLayout_13);

        verticalLayout_14 = new QVBoxLayout();
        verticalLayout_14->setSpacing(6);
        verticalLayout_14->setObjectName(QStringLiteral("verticalLayout_14"));
        settingName_label = new QLabel(widget_6);
        settingName_label->setObjectName(QStringLiteral("settingName_label"));
        settingName_label->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(settingName_label);

        settingValue_label = new QLabel(widget_6);
        settingValue_label->setObjectName(QStringLiteral("settingValue_label"));
        settingValue_label->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(settingValue_label);

        settingValue_lineEdit = new QLineEdit(widget_6);
        settingValue_lineEdit->setObjectName(QStringLiteral("settingValue_lineEdit"));
        settingValue_lineEdit->setFocusPolicy(Qt::ClickFocus);
        settingValue_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_14->addWidget(settingValue_lineEdit);


        horizontalLayout_3->addLayout(verticalLayout_14);


        verticalLayout_15->addLayout(horizontalLayout_3);

        settingAccept_pushButton = new QPushButton(widget_6);
        settingAccept_pushButton->setObjectName(QStringLiteral("settingAccept_pushButton"));

        verticalLayout_15->addWidget(settingAccept_pushButton);

        settingRestore_pushButton = new QPushButton(widget_6);
        settingRestore_pushButton->setObjectName(QStringLiteral("settingRestore_pushButton"));

        verticalLayout_15->addWidget(settingRestore_pushButton);

        settingsRestore_pushButton = new QPushButton(widget_6);
        settingsRestore_pushButton->setObjectName(QStringLiteral("settingsRestore_pushButton"));

        verticalLayout_15->addWidget(settingsRestore_pushButton);

        settingsSave_pushButton = new QPushButton(widget_6);
        settingsSave_pushButton->setObjectName(QStringLiteral("settingsSave_pushButton"));

        verticalLayout_15->addWidget(settingsSave_pushButton);


        gridLayout_4->addLayout(verticalLayout_15, 0, 1, 2, 1);

        horizontalSpacer_5 = new QSpacerItem(40, 20, QSizePolicy::MinimumExpanding, QSizePolicy::Minimum);

        gridLayout_4->addItem(horizontalSpacer_5, 0, 2, 1, 1);


        gridLayout_3->addWidget(widget_6, 0, 0, 1, 2);

        menu_stackedWidget->addWidget(settings_page);

        gridLayout->addWidget(menu_stackedWidget, 0, 3, 5, 1);

        notifications_listWidget = new QListWidget(centralWidget);
        notifications_listWidget->setObjectName(QStringLiteral("notifications_listWidget"));
        sizePolicy.setHeightForWidth(notifications_listWidget->sizePolicy().hasHeightForWidth());
        notifications_listWidget->setSizePolicy(sizePolicy);
        notifications_listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        notifications_listWidget->setProperty("showDropIndicator", QVariant(false));
        notifications_listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        notifications_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        notifications_listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        notifications_listWidget->setSpacing(2);
        notifications_listWidget->setWordWrap(true);

        gridLayout->addWidget(notifications_listWidget, 3, 0, 1, 3);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 800, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(projectControl_action);
        menu->addAction(depends_action);
        menu->addAction(action_2);
        menu->addAction(action_3);

        retranslateUi(MainWindow);

        menu_stackedWidget->setCurrentIndex(2);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "Depends searcher ", nullptr));
        projectControl_action->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\270 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        depends_action->setText(QApplication::translate("MainWindow", "\320\240\320\260\320\267\320\275\320\276\320\265", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\224\320\265\321\200\320\265\320\262\320\276 \320\267\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\265\320\271", nullptr));
        action_2->setText(QApplication::translate("MainWindow", "\320\223\320\265\320\275\320\265\321\200\320\260\321\202\320\276\321\200 \320\277\321\200\320\276\320\265\320\272\321\202\320\276\320\262", nullptr));
        action_3->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276", nullptr));
        libs_radioButton->setText(QApplication::translate("MainWindow", "\320\221\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        apps_radioButton->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        basePath_lineEdit->setText(QString());
        basePath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \321\201 \320\277\321\200\320\276\320\265\320\272\321\202\320\260\320\274\320\270", nullptr));
        update_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\276\320\262", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\265\320\272\321\202\321\213", nullptr));
        searchProject_lineEdit->setText(QString());
        searchProject_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        cleanOutput_pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\213\320\262\320\276\320\264", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        search_lineEdit->setText(QString());
        search_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        add_pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        remove_pushButton->setText(QApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214", nullptr));
        saveChanges_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        recursiveSearch_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\240\320\265\320\272\321\203\321\200\321\201\320\270\320\262\320\275\321\213\320\271 \320\277\320\276\320\270\321\201\320\272", nullptr));
        reloadGraph_pushButton->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\320\267\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\263\321\200\320\260\321\204", nullptr));
        label_8->setText(QApplication::translate("MainWindow", "\320\246\320\265\320\273\321\214 \321\201\320\261\320\276\321\200\320\272\320\270", nullptr));
        debugTarget_radioButton->setText(QApplication::translate("MainWindow", "Debug", nullptr));
        releaseTarget_radioButton->setText(QApplication::translate("MainWindow", "Release", nullptr));
        label_7->setText(QApplication::translate("MainWindow", "\320\241\320\261\320\276\321\200\320\272\320\260", nullptr));
        buildAll_radioButton->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\265", nullptr));
        buildCurrent_radioButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\271", nullptr));
        build_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\261\320\276\321\200\320\272\320\260", nullptr));
        rebuild_pushButton->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\201\320\276\320\261\321\200\320\260\321\202\321\214", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260", nullptr));
        makeFiles_checkBox->setText(QApplication::translate("MainWindow", "Makefile", nullptr));
        qmakeStash_checkBox->setText(QApplication::translate("MainWindow", "QMake Stash", nullptr));
        lib_checkBox->setText(QApplication::translate("MainWindow", "LIB", nullptr));
        bin_checkBox->setText(QApplication::translate("MainWindow", "BIN", nullptr));
        build_checkBox->setText(QApplication::translate("MainWindow", "BUILD", nullptr));
        clean_pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_6->setText(QApplication::translate("MainWindow", "\320\220\321\200\321\205\320\270\320\262\320\270\321\200\320\276\320\262\320\260\320\275\320\270\320\265", nullptr));
        archiveAll_radioButton->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\265", nullptr));
        archiveSelected_radioButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\265", nullptr));
        archiveCurrent_radioButton->setText(QApplication::translate("MainWindow", "\320\242\320\265\320\272\321\203\321\211\320\270\320\271", nullptr));
        autoName_checkBox->setText(QApplication::translate("MainWindow", "\320\220\320\262\321\202\320\276\320\267\320\260\320\277\320\276\320\273\320\275\320\265\320\275\320\270\320\265", nullptr));
        archivePath_lineEdit->setText(QApplication::translate("MainWindow", "ProjectsArchive", nullptr));
        archivePath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\321\203\321\202\321\214 \320\264\320\273\321\217 \320\260\321\200\321\205\320\270\320\262\320\260", nullptr));
        archive_pushButton->setText(QApplication::translate("MainWindow", "\320\220\321\200\321\205\320\270\320\262\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_13->setText(QApplication::translate("MainWindow", "\320\242\320\270\320\277 \320\277\321\200\320\276\320\265\320\272\321\202\320\260 \320\264\320\273\321\217 \320\263\320\265\320\275\320\265\321\200\320\260\321\206\320\270\320\270", nullptr));
        generateLib_checkBox->setText(QApplication::translate("MainWindow", "\320\221\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\260", nullptr));
        projectName_lineEdit->setText(QApplication::translate("MainWindow", "SampleProject", nullptr));
        projectName_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\235\320\260\320\267\320\262\320\260\320\275\320\270\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        projectPath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \320\264\320\273\321\217 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        generateProject_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\263\320\265\320\275\320\265\321\200\320\270\321\200\320\276\320\262\320\260\321\202\321\214", nullptr));
        label_14->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214 \320\262 \320\277\321\200\320\276\320\265\320\272\321\202", nullptr));
        hasDeps_checkBox->setText(QApplication::translate("MainWindow", "deps.pri", nullptr));
        hasBuildPri_checkBox->setText(QApplication::translate("MainWindow", "build.pri", nullptr));
        hasGui_checkBox->setText(QApplication::translate("MainWindow", "GUI", nullptr));
        label_16->setText(QApplication::translate("MainWindow", "\320\235\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        settingSearch_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        label_15->setText(QApplication::translate("MainWindow", "\320\230\320\267\320\274\320\265\320\275\320\265\320\275\320\270\320\265 \320\275\320\260\321\201\321\202\321\200\320\276\320\271\320\272\320\270", nullptr));
        label_10->setText(QApplication::translate("MainWindow", "\320\230\320\274\321\217", nullptr));
        label_11->setText(QApplication::translate("MainWindow", "\320\227\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        label_12->setText(QApplication::translate("MainWindow", "\320\235\320\276\320\262\320\276\320\265", nullptr));
        settingName_label->setText(QApplication::translate("MainWindow", "\320\235\320\265 \320\262\321\213\320\261\321\200\320\260\320\275\320\276", nullptr));
        settingValue_label->setText(QApplication::translate("MainWindow", "\320\235\320\265\321\202", nullptr));
        settingValue_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\222\320\277\320\270\321\210\320\270\321\202\320\265 \320\267\320\275\320\260\321\207\320\265\320\275\320\270\320\265", nullptr));
        settingAccept_pushButton->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\270\320\274\320\265\320\275\320\270\321\202\321\214", nullptr));
        settingRestore_pushButton->setText(QApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\270\320\267\320\275\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265", nullptr));
        settingsRestore_pushButton->setText(QApplication::translate("MainWindow", "\320\222\320\276\321\201\321\201\321\202\320\260\320\275\320\276\320\262\320\270\321\202\321\214 \320\270\320\267\320\275\320\260\321\207\320\260\320\273\321\214\320\275\320\276\320\265 \320\222\320\241\320\201", nullptr));
        settingsSave_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\272\320\276\320\275\321\204\320\270\320\263\321\203\321\200\320\260\321\206\320\270\321\216", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\274\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
