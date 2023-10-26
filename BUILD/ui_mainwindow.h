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
#include <QtWidgets/QComboBox>
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
    QStackedWidget *stackedWidget;
    QWidget *page;
    QVBoxLayout *verticalLayout_5;
    QHBoxLayout *horizontalLayout_5;
    QVBoxLayout *verticalLayout_3;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *project_comboBox;
    QLabel *label_4;
    QCheckBox *makeFiles_checkBox;
    QCheckBox *lib_checkBox;
    QCheckBox *bin_checkBox;
    QCheckBox *build_checkBox;
    QPushButton *clean_pushButton;
    QVBoxLayout *verticalLayout_4;
    QLabel *label_5;
    QRadioButton *libs_radioButton;
    QRadioButton *apps_radioButton;
    QPushButton *build_pushButton;
    QPushButton *rebuild_pushButton;
    QSpacerItem *verticalSpacer_3;
    QSpacerItem *horizontalSpacer_4;
    QWidget *page_2;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *label_2;
    QListWidget *addedLibs_listWidget;
    QProgressBar *progressBar;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_pushButton;
    QPushButton *remove_pushButton;
    QPushButton *saveChanges_pushButton;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_7;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *basePath_lineEdit;
    QPushButton *acceptBasePath_pushButton;
    QVBoxLayout *verticalLayout;
    QPushButton *update_pushButton;
    QLabel *label_3;
    QListWidget *avaliableLibs_listWidget;
    QLineEdit *search_lineEdit;
    QSpacerItem *horizontalSpacer_3;
    QMenuBar *menuBar;
    QMenu *menu;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(1350, 628);
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
        stackedWidget = new QStackedWidget(centralWidget);
        stackedWidget->setObjectName(QStringLiteral("stackedWidget"));
        page = new QWidget();
        page->setObjectName(QStringLiteral("page"));
        verticalLayout_5 = new QVBoxLayout(page);
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setContentsMargins(11, 11, 11, 11);
        verticalLayout_5->setObjectName(QStringLiteral("verticalLayout_5"));
        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setSpacing(6);
        horizontalLayout_5->setObjectName(QStringLiteral("horizontalLayout_5"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(2);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        verticalLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(0);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(page);
        label->setObjectName(QStringLiteral("label"));
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(label->sizePolicy().hasHeightForWidth());
        label->setSizePolicy(sizePolicy);
        label->setAlignment(Qt::AlignRight|Qt::AlignTrailing|Qt::AlignVCenter);

        horizontalLayout->addWidget(label);

        project_comboBox = new QComboBox(page);
        project_comboBox->setObjectName(QStringLiteral("project_comboBox"));

        horizontalLayout->addWidget(project_comboBox);


        verticalLayout_3->addLayout(horizontalLayout);

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

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(0);
        verticalLayout_4->setObjectName(QStringLiteral("verticalLayout_4"));
        label_5 = new QLabel(page);
        label_5->setObjectName(QStringLiteral("label_5"));
        sizePolicy.setHeightForWidth(label_5->sizePolicy().hasHeightForWidth());
        label_5->setSizePolicy(sizePolicy);
        label_5->setAlignment(Qt::AlignCenter);

        verticalLayout_4->addWidget(label_5);

        libs_radioButton = new QRadioButton(page);
        libs_radioButton->setObjectName(QStringLiteral("libs_radioButton"));
        libs_radioButton->setChecked(true);

        verticalLayout_4->addWidget(libs_radioButton);

        apps_radioButton = new QRadioButton(page);
        apps_radioButton->setObjectName(QStringLiteral("apps_radioButton"));

        verticalLayout_4->addWidget(apps_radioButton);

        build_pushButton = new QPushButton(page);
        build_pushButton->setObjectName(QStringLiteral("build_pushButton"));

        verticalLayout_4->addWidget(build_pushButton);

        rebuild_pushButton = new QPushButton(page);
        rebuild_pushButton->setObjectName(QStringLiteral("rebuild_pushButton"));

        verticalLayout_4->addWidget(rebuild_pushButton);


        verticalLayout_3->addLayout(verticalLayout_4);

        verticalSpacer_3 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer_3);


        horizontalLayout_5->addLayout(verticalLayout_3);

        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer_4);


        verticalLayout_5->addLayout(horizontalLayout_5);

        stackedWidget->addWidget(page);
        page_2 = new QWidget();
        page_2->setObjectName(QStringLiteral("page_2"));
        gridLayout = new QGridLayout(page_2);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
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
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(addedLibs_listWidget->sizePolicy().hasHeightForWidth());
        addedLibs_listWidget->setSizePolicy(sizePolicy1);

        verticalLayout_2->addWidget(addedLibs_listWidget);

        progressBar = new QProgressBar(page_2);
        progressBar->setObjectName(QStringLiteral("progressBar"));
        progressBar->setMaximumSize(QSize(16777215, 40));
        progressBar->setValue(0);
        progressBar->setTextVisible(true);

        verticalLayout_2->addWidget(progressBar);


        gridLayout->addLayout(verticalLayout_2, 0, 1, 1, 1);

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

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_6);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);


        gridLayout->addLayout(horizontalLayout_4, 1, 1, 1, 1);

        stackedWidget->addWidget(page_2);

        gridLayout_2->addWidget(stackedWidget, 0, 2, 3, 1);

        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(2);
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

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(1);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        update_pushButton = new QPushButton(centralWidget);
        update_pushButton->setObjectName(QStringLiteral("update_pushButton"));
        sizePolicy.setHeightForWidth(update_pushButton->sizePolicy().hasHeightForWidth());
        update_pushButton->setSizePolicy(sizePolicy);
        update_pushButton->setMinimumSize(QSize(0, 0));

        verticalLayout->addWidget(update_pushButton);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Fixed);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(label_3->sizePolicy().hasHeightForWidth());
        label_3->setSizePolicy(sizePolicy2);
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        avaliableLibs_listWidget = new QListWidget(centralWidget);
        avaliableLibs_listWidget->setObjectName(QStringLiteral("avaliableLibs_listWidget"));
        sizePolicy1.setHeightForWidth(avaliableLibs_listWidget->sizePolicy().hasHeightForWidth());
        avaliableLibs_listWidget->setSizePolicy(sizePolicy1);

        verticalLayout->addWidget(avaliableLibs_listWidget);

        search_lineEdit = new QLineEdit(centralWidget);
        search_lineEdit->setObjectName(QStringLiteral("search_lineEdit"));
        search_lineEdit->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(search_lineEdit);


        verticalLayout_7->addLayout(verticalLayout);


        gridLayout_2->addLayout(verticalLayout_7, 0, 0, 1, 2);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer_3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1350, 23));
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
        label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\271 \320\277\321\200\320\276\320\265\320\272\321\202:", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260", nullptr));
        makeFiles_checkBox->setText(QApplication::translate("MainWindow", "Makefile", nullptr));
        lib_checkBox->setText(QApplication::translate("MainWindow", "LIB", nullptr));
        bin_checkBox->setText(QApplication::translate("MainWindow", "BIN", nullptr));
        build_checkBox->setText(QApplication::translate("MainWindow", "BUILD", nullptr));
        clean_pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        label_5->setText(QApplication::translate("MainWindow", "\320\236\321\202\320\276\320\261\321\200\320\260\320\267\320\270\321\202\321\214 \321\202\320\276\320\273\321\214\320\272\320\276", nullptr));
        libs_radioButton->setText(QApplication::translate("MainWindow", "\320\221\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        apps_radioButton->setText(QApplication::translate("MainWindow", "\320\237\321\200\320\276\320\263\321\200\320\260\320\274\320\274\321\213", nullptr));
        build_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\261\320\276\321\200\320\272\320\260", nullptr));
        rebuild_pushButton->setText(QApplication::translate("MainWindow", "\320\237\320\265\321\200\320\265\321\201\320\276\320\261\321\200\320\260\321\202\321\214", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        add_pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        remove_pushButton->setText(QApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214", nullptr));
        saveChanges_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214", nullptr));
        basePath_lineEdit->setText(QApplication::translate("MainWindow", "/home/lazarev_as/workspace/project", nullptr));
        basePath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \321\201 \320\277\321\200\320\276\320\265\320\272\321\202\320\260\320\274\320\270", nullptr));
        acceptBasePath_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\272", nullptr));
        update_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272 \320\277\321\200\320\276\320\265\320\272\321\202\320\276\320\262", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\321\213", nullptr));
        search_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\237\320\276\320\270\321\201\320\272", nullptr));
        menu->setTitle(QApplication::translate("MainWindow", "\320\234\320\265\320\275\321\216", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
