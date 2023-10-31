/********************************************************************************
** Form generated from reading UI file 'dependencygraphwidget.ui'
**
** Created by: Qt User Interface Compiler version 5.11.0
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_DEPENDENCYGRAPHWIDGET_H
#define UI_DEPENDENCYGRAPHWIDGET_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QButtonGroup>
#include <QtWidgets/QHeaderView>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_DependencyGraphWidget
{
public:

    void setupUi(QWidget *DependencyGraphWidget)
    {
        if (DependencyGraphWidget->objectName().isEmpty())
            DependencyGraphWidget->setObjectName(QStringLiteral("DependencyGraphWidget"));
        DependencyGraphWidget->resize(400, 300);

        retranslateUi(DependencyGraphWidget);

        QMetaObject::connectSlotsByName(DependencyGraphWidget);
    } // setupUi

    void retranslateUi(QWidget *DependencyGraphWidget)
    {
        DependencyGraphWidget->setWindowTitle(QApplication::translate("DependencyGraphWidget", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class DependencyGraphWidget: public Ui_DependencyGraphWidget {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_DEPENDENCYGRAPHWIDGET_H
