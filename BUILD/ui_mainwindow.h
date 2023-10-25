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
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QToolBar>
#include <QtWidgets/QVBoxLayout>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QHBoxLayout *horizontalLayout_3;
    QLineEdit *basePath_lineEdit;
    QPushButton *acceptBasePath_pushButton;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QComboBox *project_comboBox;
    QVBoxLayout *verticalLayout;
    QListWidget *avaliableLibs_listWidget;
    QLabel *label_3;
    QPushButton *update_pushButton;
    QVBoxLayout *verticalLayout_2;
    QListWidget *addedLibs_listWidget;
    QLabel *label_2;
    QVBoxLayout *verticalLayout_3;
    QLabel *label_4;
    QCheckBox *makeFiles_checkBox;
    QCheckBox *lib_checkBox;
    QCheckBox *bin_checkBox;
    QCheckBox *build_checkBox;
    QPushButton *clean_pushButton;
    QGridLayout *gridLayout;
    QPushButton *saveBackup_pushButton;
    QSpacerItem *verticalSpacer;
    QHBoxLayout *horizontalLayout_2;
    QPushButton *add_pushButton;
    QPushButton *remove_pushButton;
    QSpacerItem *horizontalSpacer_3;
    QSpacerItem *horizontalSpacer_2;
    QPushButton *loadBackup_pushButton;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QStringLiteral("MainWindow"));
        MainWindow->resize(808, 539);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QStringLiteral("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QStringLiteral("gridLayout_2"));
        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QStringLiteral("horizontalLayout_3"));
        basePath_lineEdit = new QLineEdit(centralWidget);
        basePath_lineEdit->setObjectName(QStringLiteral("basePath_lineEdit"));

        horizontalLayout_3->addWidget(basePath_lineEdit);

        acceptBasePath_pushButton = new QPushButton(centralWidget);
        acceptBasePath_pushButton->setObjectName(QStringLiteral("acceptBasePath_pushButton"));

        horizontalLayout_3->addWidget(acceptBasePath_pushButton);


        gridLayout_2->addLayout(horizontalLayout_3, 0, 0, 1, 1);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QStringLiteral("horizontalLayout"));
        label = new QLabel(centralWidget);
        label->setObjectName(QStringLiteral("label"));
        label->setAlignment(Qt::AlignCenter);

        horizontalLayout->addWidget(label);

        project_comboBox = new QComboBox(centralWidget);
        project_comboBox->setObjectName(QStringLiteral("project_comboBox"));

        horizontalLayout->addWidget(project_comboBox);


        gridLayout_2->addLayout(horizontalLayout, 0, 1, 1, 1);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QStringLiteral("verticalLayout"));
        avaliableLibs_listWidget = new QListWidget(centralWidget);
        avaliableLibs_listWidget->setObjectName(QStringLiteral("avaliableLibs_listWidget"));

        verticalLayout->addWidget(avaliableLibs_listWidget);

        label_3 = new QLabel(centralWidget);
        label_3->setObjectName(QStringLiteral("label_3"));
        label_3->setAlignment(Qt::AlignCenter);

        verticalLayout->addWidget(label_3);

        update_pushButton = new QPushButton(centralWidget);
        update_pushButton->setObjectName(QStringLiteral("update_pushButton"));

        verticalLayout->addWidget(update_pushButton);


        gridLayout_2->addLayout(verticalLayout, 1, 0, 1, 1);

        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QStringLiteral("verticalLayout_2"));
        addedLibs_listWidget = new QListWidget(centralWidget);
        addedLibs_listWidget->setObjectName(QStringLiteral("addedLibs_listWidget"));

        verticalLayout_2->addWidget(addedLibs_listWidget);

        label_2 = new QLabel(centralWidget);
        label_2->setObjectName(QStringLiteral("label_2"));
        label_2->setAlignment(Qt::AlignCenter);

        verticalLayout_2->addWidget(label_2);


        gridLayout_2->addLayout(verticalLayout_2, 1, 1, 1, 1);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QStringLiteral("verticalLayout_3"));
        label_4 = new QLabel(centralWidget);
        label_4->setObjectName(QStringLiteral("label_4"));
        label_4->setAlignment(Qt::AlignCenter);

        verticalLayout_3->addWidget(label_4);

        makeFiles_checkBox = new QCheckBox(centralWidget);
        makeFiles_checkBox->setObjectName(QStringLiteral("makeFiles_checkBox"));
        makeFiles_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(makeFiles_checkBox);

        lib_checkBox = new QCheckBox(centralWidget);
        lib_checkBox->setObjectName(QStringLiteral("lib_checkBox"));
        lib_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(lib_checkBox);

        bin_checkBox = new QCheckBox(centralWidget);
        bin_checkBox->setObjectName(QStringLiteral("bin_checkBox"));
        bin_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(bin_checkBox);

        build_checkBox = new QCheckBox(centralWidget);
        build_checkBox->setObjectName(QStringLiteral("build_checkBox"));
        build_checkBox->setFocusPolicy(Qt::NoFocus);

        verticalLayout_3->addWidget(build_checkBox);

        clean_pushButton = new QPushButton(centralWidget);
        clean_pushButton->setObjectName(QStringLiteral("clean_pushButton"));

        verticalLayout_3->addWidget(clean_pushButton);


        gridLayout_2->addLayout(verticalLayout_3, 2, 0, 1, 1);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QStringLiteral("gridLayout"));
        saveBackup_pushButton = new QPushButton(centralWidget);
        saveBackup_pushButton->setObjectName(QStringLiteral("saveBackup_pushButton"));

        gridLayout->addWidget(saveBackup_pushButton, 1, 1, 1, 1);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        gridLayout->addItem(verticalSpacer, 4, 1, 1, 1);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QStringLiteral("horizontalLayout_2"));
        add_pushButton = new QPushButton(centralWidget);
        add_pushButton->setObjectName(QStringLiteral("add_pushButton"));

        horizontalLayout_2->addWidget(add_pushButton);

        remove_pushButton = new QPushButton(centralWidget);
        remove_pushButton->setObjectName(QStringLiteral("remove_pushButton"));

        horizontalLayout_2->addWidget(remove_pushButton);


        gridLayout->addLayout(horizontalLayout_2, 0, 1, 1, 1);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_3, 0, 2, 1, 1);

        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout->addItem(horizontalSpacer_2, 0, 0, 1, 1);

        loadBackup_pushButton = new QPushButton(centralWidget);
        loadBackup_pushButton->setObjectName(QStringLiteral("loadBackup_pushButton"));

        gridLayout->addWidget(loadBackup_pushButton, 2, 1, 1, 1);


        gridLayout_2->addLayout(gridLayout, 2, 1, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QStringLiteral("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 808, 23));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QStringLiteral("mainToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QStringLiteral("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "MainWindow", nullptr));
        basePath_lineEdit->setText(QApplication::translate("MainWindow", "/home/lazarev_as/workspace/project", nullptr));
        basePath_lineEdit->setPlaceholderText(QApplication::translate("MainWindow", "\320\224\320\270\321\200\320\265\320\272\321\202\320\276\321\200\320\270\321\217 \321\201 \320\277\321\200\320\276\320\265\320\272\321\202\320\260\320\274\320\270", nullptr));
        acceptBasePath_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\272", nullptr));
        label->setText(QApplication::translate("MainWindow", "\320\222\321\213\320\261\321\200\320\260\320\275\320\275\321\213\320\271 \320\277\321\200\320\276\320\265\320\272\321\202:", nullptr));
        label_3->setText(QApplication::translate("MainWindow", "\320\224\320\276\321\201\321\202\321\203\320\277\320\275\321\213\320\265 \320\277\321\200\320\276\320\265\320\272\321\202\321\213", nullptr));
        update_pushButton->setText(QApplication::translate("MainWindow", "\320\236\320\261\320\275\320\276\320\262\320\270\321\202\321\214 \321\201\320\277\320\270\321\201\320\276\320\272", nullptr));
        label_2->setText(QApplication::translate("MainWindow", "\320\237\320\276\320\264\320\272\320\273\321\216\321\207\320\265\320\275\320\275\321\213\320\265 \320\261\320\270\320\261\320\273\320\270\320\276\321\202\320\265\320\272\320\270", nullptr));
        label_4->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\272\320\260", nullptr));
        makeFiles_checkBox->setText(QApplication::translate("MainWindow", "Makefile", nullptr));
        lib_checkBox->setText(QApplication::translate("MainWindow", "LIB", nullptr));
        bin_checkBox->setText(QApplication::translate("MainWindow", "BIN", nullptr));
        build_checkBox->setText(QApplication::translate("MainWindow", "BUILD", nullptr));
        clean_pushButton->setText(QApplication::translate("MainWindow", "\320\236\321\207\320\270\321\201\321\202\320\270\321\202\321\214", nullptr));
        saveBackup_pushButton->setText(QApplication::translate("MainWindow", "\320\241\320\276\321\205\321\200\320\260\320\275\320\270\321\202\321\214 \320\261\321\215\320\272\320\260\320\277", nullptr));
        add_pushButton->setText(QApplication::translate("MainWindow", "\320\224\320\276\320\261\320\260\320\262\320\270\321\202\321\214", nullptr));
        remove_pushButton->setText(QApplication::translate("MainWindow", "\320\243\320\261\321\200\320\260\321\202\321\214", nullptr));
        loadBackup_pushButton->setText(QApplication::translate("MainWindow", "\320\227\320\260\320\263\321\200\321\203\320\267\320\270\321\202\321\214 \320\261\321\215\320\272\320\260\320\277", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
