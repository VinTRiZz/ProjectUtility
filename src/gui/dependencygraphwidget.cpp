#include "dependencygraphwidget.h"
#include "ui_dependencygraphwidget.h"

#include <QPainter>

struct DependencyGraphWidget::Impl
{
    QPainter * m_painter {nullptr};
    QBrush * m_shapeBrush {nullptr};
    QBrush * m_arrowBrush {nullptr};
};

DependencyGraphWidget::DependencyGraphWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::DependencyGraphWidget)
{
    ui->setupUi(this);
}

DependencyGraphWidget::~DependencyGraphWidget()
{
    delete ui;
}

void DependencyGraphWidget::addDependency(const QString &who, const QVector<QString> &from)
{

}
