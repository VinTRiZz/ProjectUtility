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
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_7;
    QVBoxLayout *verticalLayout_10;
    QLineEdit *basePath_lineEdit;
    QPushButton *update_pushButton;
    QLabel *label;
    QListWidget *projects_listWidget;
    QLineEdit *searchProject_lineEdit;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QRadioButton *libs_radioButton;
    QRadioButton *apps_radioButton;
    QSpacerItem *horizontalSpacer_2;
    QSpacerItem *horizontalSpacer;
    QListWidget *notifications_listWidget;
    QLabel *label_9;
    QPushButton *cleanOutput_pushButton;
    QStackedWidget *menu_stackedWidget;
    QWidget *page;
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
    QSpacerItem *verticalSpacer_4;
    QScrollArea *graph_scrollArea;
    QWidget *scrollAreaWidgetContents;
    QWidget *page_2;
    QGridLayout *gridLayout_2;
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
    QProgressBar *progressBar;
    QWidget *widget_5;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QCheckBox *makeFiles_checkBox;
    QCheckBox *qmakeStash_checkBox;
    QCheckBox *lib_checkBox;
    QCheckBox *bin_checkBox;
    QCheckBox *build_checkBox;
    QPushButton *clean_pushButton;
    QWidget *widget_4;
    QVBoxLayout *verticalLayout_12;
    QLabel *label_6;
    QRadioButton *archiveAll_radioButton;
    QRadioButton *archiveSelected_radioButton;
    QRadioButton *archiveCurrent_radioButton;
    QCheckBox *autoName_checkBox;
    QLineEdit *archivePath_lineEdit;
    QPushButton *archive_pushButton;
    QSpacerItem *verticalSpacer_2;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menu;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1021, 715);
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
"}\n"
"\n"
""));
        projectControl_action = new QAction(MainWindow);
        projectControl_action->setObjectName(QStringLiteral("projectControl_action"));
        depends_action = new QAction(MainWindow);
        depends_action->setObjectName(QStringLiteral("depends_action"));
        action = new QAction(MainWindow);
        action->setObjectName(QStringLiteral("action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        centralWidget->setStyleSheet(QStringLiteral(""));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(0);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));
        basePath_lineEdit = new QLineEdit(centralWidget);
        basePath_lineEdit->setObjectName(QStringLiteral("basePath_lineEdit"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(basePath_lineEdit->sizePolicy().hasHeightForWidth());
        basePath_lineEdit->setSizePolicy(sizePolicy);
        basePath_lineEdit->setMaximumSize(QSize(350, 16777215));
        basePath_lineEdit->setStyleSheet(QStringLiteral("color: rgb(167, 167, 167);"));

        verticalLayout_10->addWidget(basePath_lineEdit);


        verticalLayout_7->addLayout(verticalLayout_10);

        update_pushButton = new QPushButton(centralWidget);
        update_pushButton->setObjectName(QStringLiteral("update_pushButton"));
        sizePolicy.setHeightForWidth(update_pushButton->sizePolicy().hasHeightForWidth());
        update_pushButton->setSizePolicy(sizePolicy);
        update_pushButton->setMinimumSize(QSize(0, 0));
        update_pushButton->setMaximumSize(QSize(500, 16777215));
        update_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_7->addWidget(update_pushButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setMaximumSize(QSize(500, 16777215));
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label);

        projects_listWidget = new QListWidget(centralWidget);
        projects_listWidget->setObjectName(QStringLiteral("projects_listWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Preferred, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(projects_listWidget->sizePolicy().hasHeightForWidth());
        projects_listWidget->setSizePolicy(sizePolicy1);
        projects_listWidget->setMaximumSize(QSize(500, 16777215));
        projects_listWidget->setFocusPolicy(Qt::NoFocus);
        projects_listWidget->setStyleSheet(QStringLiteral(""));
        projects_listWidget->setSelectionMode(QAbstractItemView::ExtendedSelection);
        projects_listWidget->setSortingEnabled(true);

        verticalLayout_7->addWidget(projects_listWidget);

        searchProject_lineEdit = new QLineEdit(centralWidget);
        searchProject_lineEdit->setObjectName(QStringLiteral("searchProject_lineEdit"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(searchProject_lineEdit->sizePolicy().hasHeightForWidth());
        searchProject_lineEdit->setSizePolicy(sizePolicy2);
        searchProject_lineEdit->setMaximumSize(QSize(500, 16777215));
        searchProject_lineEdit->setStyleSheet(QStringLiteral(""));
        searchProject_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(searchProject_lineEdit);


        gridLayout->addLayout(verticalLayout_7, 1, 0, 1, 3);

        widget = new QWidget(centralWidget);
        widget->setObjectName(QStringLiteral("widget"));
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
        widget->setStyleSheet(QStringLiteral(""));
        verticalLayout_5 = new QVBoxLayout(widget);
        verticalLayout_5->setSpacing(0);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        verticalLayout_5->setContentsMargins(0, 0, 0, 0);
        label_5 = new QLabel(widget);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
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

        horizontalSpacer_2 = new QSpacerItem(30, 20, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Preferred, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer, 0, 2, 1, 1);

        notifications_listWidget = new QListWidget(centralWidget);
        notifications_listWidget->setObjectName(QStringLiteral("notifications_listWidget"));
        sizePolicy2.setHeightForWidth(notifications_listWidget->sizePolicy().hasHeightForWidth());
        notifications_listWidget->setSizePolicy(sizePolicy2);
        notifications_listWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
        notifications_listWidget->setProperty("showDropIndicator", QVariant(false));
        notifications_listWidget->setSelectionMode(QAbstractItemView::NoSelection);
        notifications_listWidget->setVerticalScrollMode(QAbstractItemView::ScrollPerPixel);
        notifications_listWidget->setHorizontalScrollMode(QAbstractItemView::ScrollPerPixel);
        notifications_listWidget->setSpacing(2);
        notifications_listWidget->setWordWrap(true);

        gridLayout->addWidget(notifications_listWidget, 3, 0, 1, 3);

        label_9 = new QLabel(centralWidget);
        label_9->setObjectName(QStringLiteral("label_9"));
        label_9->setAlignment(Qt::AlignCenter);

        gridLayout->addWidget(label_9, 2, 0, 1, 3);

        cleanOutput_pushButton = new QPushButton(centralWidget);
        cleanOutput_pushButton->setObjectName(QStringLiteral("cleanOutput_pushButton"));

        gridLayout->addWidget(cleanOutput_pushButton, 4, 0, 1, 3);

        menu_stackedWidget = new QStackedWidget(centralWidget);
        menu_stackedWidget->setObjectName(QStringLiteral("menu_stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        horizontalLayout_4 = new QHBoxLayout(page);
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
        label_3 = new QLabel(page);
        label_3->setObjectName(QStringLiteral("label_3"));
        sizePolicy.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        avaliableLibs_listWidget = new QListWidget(page);
        avaliableLibs_listWidget->setObjectName(QStringLiteral("avaliableLibs_listWidget"));
        sizePolicy2.setHeightForWidth(avaliableLibs_listWidget->sizePolicy().hasHeightForWidth());
        avaliableLibs_listWidget->setSizePolicy(sizePolicy2);

        verticalLayout->addWidget(avaliableLibs_listWidget);

        search_lineEdit = new QLineEdit(page);
        search_lineEdit->setObjectName(QStringLiteral("search_lineEdit"));
        sizePolicy.setHeightForWidth(search_lineEdit->sizePolicy().hasHeightForWidth());
        search_lineEdit->setSizePolicy(sizePolicy);
        search_lineEdit->setStyleSheet(QStringLiteral(""));
        search_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(search_lineEdit);


        verticalLayout_6->addLayout(verticalLayout);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        add_pushButton = new QPushButton(page);
        add_pushButton->setObjectName(QStringLiteral("add_pushButton"));
        sizePolicy.setHeightForWidth(add_pushButton->sizePolicy().hasHeightForWidth());
        add_pushButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(add_pushButton);

        remove_pushButton = new QPushButton(page);
        remove_pushButton->setObjectName(QStringLiteral("remove_pushButton"));
        sizePolicy.setHeightForWidth(remove_pushButton->sizePolicy().hasHeightForWidth());
        remove_pushButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(remove_pushButton);

        saveChanges_pushButton = new QPushButton(page);
        saveChanges_pushButton->setObjectName(QStringLiteral("saveChanges_pushButton"));
        sizePolicy.setHeightForWidth(saveChanges_pushButton->sizePolicy().hasHeightForWidth());
        saveChanges_pushButton->setSizePolicy(sizePolicy);

        horizontalLayout_2->addWidget(saveChanges_pushButton);


        verticalLayout_6->addLayout(horizontalLayout_2);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(page);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        addedLibs_listWidget = new QListWidget(page);
        addedLibs_listWidget->setObjectName(QStringLiteral("addedLibs_listWidget"));
        sizePolicy2.setHeightForWidth(addedLibs_listWidget->sizePolicy().hasHeightForWidth());
        addedLibs_listWidget->setSizePolicy(sizePolicy2);

        verticalLayout_2->addWidget(addedLibs_listWidget);


        verticalLayout_6->addLayout(verticalLayout_2);

        verticalSpacer_4 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_4);


        horizontalLayout_4->addLayout(verticalLayout_6);

        graph_scrollArea = new QScrollArea(page);
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
        scrollAreaWidgetContents->setGeometry(QRect(0, 0, 46, 28));
        graph_scrollArea->setWidget(scrollAreaWidgetContents);

        horizontalLayout_4->addWidget(graph_scrollArea);

        menu_stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout_2 = new QGridLayout(page_2);
        gridLayout_2->setSpacing(3);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        gridLayout_2->setContentsMargins(0, 0, 0, 0);
        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(3);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        widget_3 = new QWidget(page_2);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        sizePolicy2.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy2);
        widget_3->setStyleSheet(QStringLiteral(""));
        verticalLayout_8 = new QVBoxLayout(widget_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        label_8 = new QLabel(widget_3);
        label_8->setObjectName(QStringLiteral("label_8"));
        sizePolicy.setHeightForWidth(label_8->sizePolicy().hasHeightForWidth());
        label_8->setSizePolicy(sizePolicy);
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

        widget_2 = new QWidget(page_2);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy2.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy2);
        widget_2->setStyleSheet(QStringLiteral(""));
        verticalLayout_11 = new QVBoxLayout(widget_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        label_7 = new QLabel(widget_2);
        label_7->setObjectName(QStringLiteral("label_7"));
        sizePolicy.setHeightForWidth(label_7->sizePolicy().hasHeightForWidth());
        label_7->setSizePolicy(sizePolicy);
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
        build_pushButton = new QPushButton(page_2);
        build_pushButton->setObjectName(QStringLiteral("build_pushButton"));
        build_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(build_pushButton);

        rebuild_pushButton = new QPushButton(page_2);
        rebuild_pushButton->setObjectName(QStringLiteral("rebuild_pushButton"));
        rebuild_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_4->addWidget(rebuild_pushButton);

        progressBar = new QProgressBar(page_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        sizePolicy.setHeightForWidth(progressBar->sizePolicy().hasHeightForWidth());
        progressBar->setSizePolicy(sizePolicy);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progressBar->setOrientation(Qt::Horizontal);

        verticalLayout_4->addWidget(progressBar);


        verticalLayout_9->addLayout(verticalLayout_4);


        gridLayout_2->addLayout(verticalLayout_9, 0, 0, 1, 1);

        widget_5 = new QWidget(page_2);
        widget_5->setObjectName(QStringLiteral("widget_5"));
        widget_5->setStyleSheet(QStringLiteral(""));
        verticalLayout_3 = new QVBoxLayout(widget_5);
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setContentsMargins(11, 11, 11, 11);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(widget_5);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
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

        widget_4 = new QWidget(page_2);
        widget_4->setObjectName(QStringLiteral("widget_4"));
        sizePolicy2.setHeightForWidth(widget_4->sizePolicy().hasHeightForWidth());
        widget_4->setSizePolicy(sizePolicy2);
        widget_4->setStyleSheet(QStringLiteral(""));
        verticalLayout_12 = new QVBoxLayout(widget_4);
        verticalLayout_12->setSpacing(2);
        verticalLayout_12->setContentsMargins(11, 11, 11, 11);
        verticalLayout_12->setObjectName(QStringLiteral("verticalLayout_12"));
        verticalLayout_12->setContentsMargins(2, 2, 2, 2);
        label_6 = new QLabel(widget_4);
        label_6->setObjectName(QStringLiteral("label_6"));
        sizePolicy.setHeightForWidth(label_6->sizePolicy().hasHeightForWidth());
        label_6->setSizePolicy(sizePolicy);
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
        sizePolicy.setHeightForWidth(archivePath_lineEdit->sizePolicy().hasHeightForWidth());
        archivePath_lineEdit->setSizePolicy(sizePolicy);
        archivePath_lineEdit->setStyleSheet(QStringLiteral("color: rgb(215, 215, 215);"));
        archivePath_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_12->addWidget(archivePath_lineEdit);

        archive_pushButton = new QPushButton(widget_4);
        archive_pushButton->setObjectName(QStringLiteral("archive_pushButton"));
        archive_pushButton->setStyleSheet(QStringLiteral(""));

        verticalLayout_12->addWidget(archive_pushButton);


        gridLayout_2->addWidget(widget_4, 1, 0, 1, 1);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer_2, 2, 0, 1, 1);

        verticalSpacer = new QSpacerItem(119, 431, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout_2->addItem(verticalSpacer, 1, 1, 2, 1);

        menu_stackedWidget->addWidget(page_2);

        gridLayout->addWidget(menu_stackedWidget, 0, 3, 5, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1021, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(projectControl_action);
        menu->addAction(depends_action);

        retranslateUi(MainWindow);

        menu_stackedWidget->setCurrentIndex(1);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        projectControl_action->setText(QApplication::translate("MainWindow", "\320\241\320\261\320\276\321\200\320\272\320\260, \321\207\320\270\321\201\321\202\320\272\320\260 \320\270 \320\260\321\200\321\205\320\270\320\262\320\260\321\206\320\270\321\217", nullptr));
        depends_action->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\270 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        action->setText(QApplication::translate("MainWindow", "\320\224\320\265\321\200\320\265\320\262\320\276 \320\267\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\265\320\271", nullptr));
        basePath_lineEdit->setText(QApplication::translate("MainWindow", "/home/lazarev_as/workspace/project", nullptr));
        basePath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \321\201 \320\277\321\200\320\276\320\265\320\272\321\202\320\260\320\274\320\270", nullptr));
        update_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\276\320\262", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\265\320\272\321\202\321\213", nullptr));
        searchProject_lineEdit->setText(QString());
        searchProject_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276", nullptr));
        libs_radioButton->setText(QApplication::translate("MainWindow", "\320\221\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        apps_radioButton->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        label_9->setText(QApplication::translate("MainWindow", "\320\241\320\276\320\276\320\261\321\211\320\265\320\275\320\270\321\217 \320\277\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        cleanOutput_pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214 \320\262\321\213\320\262\320\276\320\264", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        search_lineEdit->setText(QString());
        search_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        add_pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        remove_pushButton->setText(QApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214", nullptr));
        saveChanges_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
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
        menu->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\274\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
