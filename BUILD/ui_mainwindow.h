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
#include <QtWidgets/QPushButton>
#include <QtWidgets/QRadioButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStackedWidget>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *projectControl_action;
    QAction *depends_action;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *basePath_lineEdit;
    QPushButton *acceptBasePath_pushButton;
    QPushButton *update_pushButton;
    QLabel *label;
    QListWidget *projects_listWidget;
    QLineEdit *searchProject_lineEdit;
    QStackedWidget *stackedWidget;
    QWidget *page;
    QGridLayout *gridLayout_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_9;
    QVBoxLayout *verticalLayout_10;
    QWidget *widget_2;
    QVBoxLayout *verticalLayout_11;
    QRadioButton *buildAll_radioButton;
    QRadioButton *buildCurrent_radioButton;
    QWidget *widget_3;
    QVBoxLayout *verticalLayout_8;
    QRadioButton *debugTarget_radioButton;
    QRadioButton *releaseTarget_radioButton;
    QVBoxLayout *verticalLayout_4;
    QPushButton *build_pushButton;
    QPushButton *rebuild_pushButton;
    QLabel *label_4;
    QCheckBox *makeFiles_checkBox;
    QCheckBox *qmakeStash_checkBox;
    QCheckBox *lib_checkBox;
    QCheckBox *bin_checkBox;
    QCheckBox *build_checkBox;
    QPushButton *clean_pushButton;
    QSpacerItem *verticalSpacer_3;
    QWidget *widget;
    QVBoxLayout *verticalLayout_5;
    QLabel *label_5;
    QRadioButton *libs_radioButton;
    QRadioButton *apps_radioButton;
    QSpacerItem *horizontalSpacer_4;
    QSpacerItem *verticalSpacer;
    QWidget *page_2;
    QGridLayout *gridLayout;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_pushButton;
    QPushButton *remove_pushButton;
    QPushButton *saveChanges_pushButton;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *addedLibs_listWidget;
    QVBoxLayout *verticalLayout;
    QLabel *label_3;
    QListWidget *avaliableLibs_listWidget;
    QLineEdit *search_lineEdit;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1214, 596);
        MainWindow->setCursor(QCursor(Qt::ArrowCursor));
        projectControl_action = new QAction(MainWindow);
        projectControl_action->setObjectName(QStringLiteral("projectControl_action"));
        depends_action = new QAction(MainWindow);
        depends_action->setObjectName(QStringLiteral("depends_action"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QStringLiteral("verticalLayout_7"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(0);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        basePath_lineEdit = new QLineEdit(centralWidget);
        basePath_lineEdit->setObjectName(QStringLiteral("basePath_lineEdit"));

        horizontalLayout_3->addWidget(basePath_lineEdit);

        acceptBasePath_pushButton = new QPushButton(centralWidget);
        acceptBasePath_pushButton->setObjectName(QStringLiteral("acceptBasePath_pushButton"));

        horizontalLayout_3->addWidget(acceptBasePath_pushButton);


        verticalLayout_7->addLayout(horizontalLayout_3);

        update_pushButton = new QPushButton(centralWidget);
        update_pushButton->setObjectName(QStringLiteral("update_pushButton"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(update_pushButton->sizePolicy().hasHeightForWidth());
        update_pushButton->setSizePolicy(sizePolicy);
        update_pushButton->setMinimumSize(QSize(0, 0));

        verticalLayout_7->addWidget(update_pushButton);

        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setLayoutDirection(Qt::LeftToRight);
        label->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(label);

        projects_listWidget = new QListWidget(centralWidget);
        projects_listWidget->setObjectName(QStringLiteral("projects_listWidget"));
        projects_listWidget->setFocusPolicy(Qt::NoFocus);
        projects_listWidget->setSortingEnabled(true);

        verticalLayout_7->addWidget(projects_listWidget);

        searchProject_lineEdit = new QLineEdit(centralWidget);
        searchProject_lineEdit->setObjectName(QStringLiteral("searchProject_lineEdit"));
        searchProject_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout_7->addWidget(searchProject_lineEdit);


        gridLayout_2->addLayout(verticalLayout_7, 0, 0, 1, 1);

        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(stackedWidget->sizePolicy().hasHeightForWidth());
        stackedWidget->setSizePolicy(sizePolicy1);
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        gridLayout_3 = new QGridLayout(page);
        gridLayout_3->setSpacing(6);
        gridLayout_3->setContentsMargins(11, 11, 11, 11);
        gridLayout_3->setObjectName(QStringLiteral("gridLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        verticalLayout_9 = new QVBoxLayout();
        verticalLayout_9->setSpacing(6);
        verticalLayout_9->setObjectName(QStringLiteral("verticalLayout_9"));
        verticalLayout_10 = new QVBoxLayout();
        verticalLayout_10->setSpacing(6);
        verticalLayout_10->setObjectName(QStringLiteral("verticalLayout_10"));

        verticalLayout_9->addLayout(verticalLayout_10);

        widget_2 = new QWidget(page);
        widget_2->setObjectName(QStringLiteral("widget_2"));
        sizePolicy.setHeightForWidth(widget_2->sizePolicy().hasHeightForWidth());
        widget_2->setSizePolicy(sizePolicy);
        verticalLayout_11 = new QVBoxLayout(widget_2);
        verticalLayout_11->setSpacing(6);
        verticalLayout_11->setContentsMargins(11, 11, 11, 11);
        verticalLayout_11->setObjectName(QStringLiteral("verticalLayout_11"));
        buildAll_radioButton = new QRadioButton(widget_2);
        buildAll_radioButton->setObjectName(QStringLiteral("buildAll_radioButton"));
        buildAll_radioButton->setChecked(true);

        verticalLayout_11->addWidget(buildAll_radioButton);

        buildCurrent_radioButton = new QRadioButton(widget_2);
        buildCurrent_radioButton->setObjectName(QStringLiteral("buildCurrent_radioButton"));

        verticalLayout_11->addWidget(buildCurrent_radioButton);


        verticalLayout_9->addWidget(widget_2);

        widget_3 = new QWidget(page);
        widget_3->setObjectName(QStringLiteral("widget_3"));
        sizePolicy.setHeightForWidth(widget_3->sizePolicy().hasHeightForWidth());
        widget_3->setSizePolicy(sizePolicy);
        verticalLayout_8 = new QVBoxLayout(widget_3);
        verticalLayout_8->setSpacing(6);
        verticalLayout_8->setContentsMargins(11, 11, 11, 11);
        verticalLayout_8->setObjectName(QStringLiteral("verticalLayout_8"));
        debugTarget_radioButton = new QRadioButton(widget_3);
        debugTarget_radioButton->setObjectName(QStringLiteral("debugTarget_radioButton"));
        debugTarget_radioButton->setChecked(true);

        verticalLayout_8->addWidget(debugTarget_radioButton);

        releaseTarget_radioButton = new QRadioButton(widget_3);
        releaseTarget_radioButton->setObjectName(QStringLiteral("releaseTarget_radioButton"));

        verticalLayout_8->addWidget(releaseTarget_radioButton);


        verticalLayout_9->addWidget(widget_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        build_pushButton = new QPushButton(page);
        build_pushButton->setObjectName(QStringLiteral("build_pushButton"));

        verticalLayout_4->addWidget(build_pushButton);

        rebuild_pushButton = new QPushButton(page);
        rebuild_pushButton->setObjectName(QStringLiteral("rebuild_pushButton"));

        verticalLayout_4->addWidget(rebuild_pushButton);


        verticalLayout_9->addLayout(verticalLayout_4);


        verticalLayout_3->addLayout(verticalLayout_9);

        label_4 = new QLabel(page);
        label_4->setObjectName(QStringLiteral("label_4"));
        sizePolicy.setHeightForWidth(label_4->sizePolicy().hasHeightForWidth());
        label_4->setSizePolicy(sizePolicy);
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        makeFiles_checkBox = new QCheckBox(page);
        makeFiles_checkBox->setObjectName(QStringLiteral("makeFiles_checkBox"));
        makeFiles_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(makeFiles_checkBox);

        qmakeStash_checkBox = new QCheckBox(page);
        qmakeStash_checkBox->setObjectName(QStringLiteral("qmakeStash_checkBox"));

        verticalLayout_3->addWidget(qmakeStash_checkBox);

        lib_checkBox = new QCheckBox(page);
        lib_checkBox->setObjectName(QStringLiteral("lib_checkBox"));
        lib_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(lib_checkBox);

        bin_checkBox = new QCheckBox(page);
        bin_checkBox->setObjectName(QStringLiteral("bin_checkBox"));
        bin_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(bin_checkBox);

        build_checkBox = new QCheckBox(page);
        build_checkBox->setObjectName(QStringLiteral("build_checkBox"));
        build_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(build_checkBox);

        clean_pushButton = new QPushButton(page);
        clean_pushButton->setObjectName(QStringLiteral("clean_pushButton"));

        verticalLayout_3->addWidget(clean_pushButton);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        gridLayout_3->addLayout(verticalLayout_3, 0, 0, 2, 1);

        widget = new QWidget(page);
        widget->setObjectName(QStringLiteral("widget"));
        QSizePolicy sizePolicy2(QSizePolicy::Fixed, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(widget->sizePolicy().hasHeightForWidth());
        widget->setSizePolicy(sizePolicy2);
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
        libs_radioButton->setChecked(true);

        verticalLayout_5->addWidget(libs_radioButton);

        apps_radioButton = new QRadioButton(widget);
        apps_radioButton->setObjectName(QStringLiteral("apps_radioButton"));

        verticalLayout_5->addWidget(apps_radioButton);


        gridLayout_3->addWidget(widget, 0, 1, 1, 1);

        horizontalSpacer_4 = new QSpacerItem(231, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_3->addItem(horizontalSpacer_4, 0, 2, 1, 1);

        verticalSpacer = new QSpacerItem(20, 370, QSizePolicy::Minimum, QSizePolicy::Minimum);

        gridLayout_3->addItem(verticalSpacer, 1, 1, 1, 1);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout = new QGridLayout(page_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(2);
        horizontalLayout_4->setObjectName(QStringLiteral("horizontalLayout_4"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer_2);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QStringLiteral("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(2);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        add_pushButton = new QPushButton(page_2);
        add_pushButton->setObjectName(QStringLiteral("add_pushButton"));

        horizontalLayout_2->addWidget(add_pushButton);

        remove_pushButton = new QPushButton(page_2);
        remove_pushButton->setObjectName(QStringLiteral("remove_pushButton"));

        horizontalLayout_2->addWidget(remove_pushButton);

        saveChanges_pushButton = new QPushButton(page_2);
        saveChanges_pushButton->setObjectName(QStringLiteral("saveChanges_pushButton"));

        horizontalLayout_2->addWidget(saveChanges_pushButton);


        verticalLayout_6->addLayout(horizontalLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_4, 2, 1, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(2);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        label_2 = new QLabel(page_2);
        label_2->setObjectName(QStringLiteral("label_2"));
        sizePolicy.setHeightForWidth(label_2->sizePolicy().hasHeightForWidth());
        label_2->setSizePolicy(sizePolicy);
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);

        addedLibs_listWidget = new QListWidget(page_2);
        addedLibs_listWidget->setObjectName(QStringLiteral("addedLibs_listWidget"));
        QSizePolicy sizePolicy3(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(addedLibs_listWidget->sizePolicy().hasHeightForWidth());
        addedLibs_listWidget->setSizePolicy(sizePolicy3);

        verticalLayout_2->addWidget(addedLibs_listWidget);


        gridLayout->addLayout(verticalLayout_2, 1, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        label_3 = new QLabel(page_2);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy4(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy4.setHorizontalStretch(0);
        sizePolicy4.setVerticalStretch(0);
        sizePolicy4.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy4);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        avaliableLibs_listWidget = new QListWidget(page_2);
        avaliableLibs_listWidget->setObjectName(QStringLiteral("avaliableLibs_listWidget"));
        sizePolicy3.setHeightForWidth(avaliableLibs_listWidget->sizePolicy().hasHeightForWidth());
        avaliableLibs_listWidget->setSizePolicy(sizePolicy3);

        verticalLayout->addWidget(avaliableLibs_listWidget);

        search_lineEdit = new QLineEdit(page_2);
        search_lineEdit->setObjectName(QStringLiteral("search_lineEdit"));
        search_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(search_lineEdit);


        gridLayout->addLayout(verticalLayout, 0, 1, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1214, 23));
        menu = new QMenu(menuBar);
        menu->setObjectName(QStringLiteral("menu"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu->menuAction());
        menu->addAction(projectControl_action);
        menu->addAction(depends_action);

        retranslateUi(MainWindow);

        stackedWidget->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        projectControl_action->setText(QApplication::translate("MainWindow", "\320\243\320\277\321\200\320\260\320\262\320\273\320\265\320\275\320\270\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\320\276\320\274", nullptr));
        depends_action->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\262\320\270\321\201\320\270\320\274\320\276\321\201\321\202\320\270 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        basePath_lineEdit->setText(QApplication::translate("MainWindow", "/home/lazarev_as/workspace/project", nullptr));
        basePath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \321\201 \320\277\321\200\320\276\320\265\320\272\321\202\320\260\320\274\320\270", nullptr));
        acceptBasePath_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\272", nullptr));
        update_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\276\320\262", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\265\320\272\321\202\321\213", nullptr));
        searchProject_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\260", nullptr));
        buildAll_radioButton->setText(QApplication::translate("MainWindow", "\320\222\321\201\320\265", nullptr));
        buildCurrent_radioButton->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\271", nullptr));
        debugTarget_radioButton->setText(QApplication::translate("MainWindow", "Debug", nullptr));
        releaseTarget_radioButton->setText(QApplication::translate("MainWindow", "Release", nullptr));
        build_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\261\320\276\321\200\320\272\320\260", nullptr));
        rebuild_pushButton->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\201\320\276\320\261\321\200\320\260\321\202\321\214", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260", nullptr));
        makeFiles_checkBox->setText(QApplication::translate("MainWindow", "Makefile", nullptr));
        qmakeStash_checkBox->setText(QApplication::translate("MainWindow", "QMake Stash", nullptr));
        lib_checkBox->setText(QApplication::translate("MainWindow", "LIB", nullptr));
        bin_checkBox->setText(QApplication::translate("MainWindow", "BIN", nullptr));
        build_checkBox->setText(QApplication::translate("MainWindow", "BUILD", nullptr));
        clean_pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276", nullptr));
        libs_radioButton->setText(QApplication::translate("MainWindow", "\320\221\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        apps_radioButton->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        add_pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        remove_pushButton->setText(QApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214", nullptr));
        saveChanges_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        search_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\321\202\321\214 \320\274\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
