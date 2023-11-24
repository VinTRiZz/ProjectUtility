#ifndef DEPENDENCYGRAPHWIDGET_H
#define DEPENDENCYGRAPHWIDGET_H

#include <QWidget>
#include "utilfunctionclass.h"
#include <memory>

namespace GraphWidget
{

struct DependencyStruct
{
    QString name {"Root"};
    QVector<DependencyStruct *> dependsFrom;

    QRect position;
    bool isApp {false};

    QPoint centerUp() const
    {
        return QPoint(position.left() + position.width() / 2, position.top());
    }

    QPoint centerDown() const
    {
        return QPoint(position.left() + position.width() / 2, position.bottom());
    }

    QPoint centerLeft() const
    {
        return QPoint(position.left(), position.top() + position.height() / 2);
    }

    QPoint centerRight() const
    {
        return QPoint(position.right(), position.top() + position.height() / 2);
    }
};

class DependencyGraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DependencyGraphWidget(QWidget *parent = 0);
    ~DependencyGraphWidget();

    void setHead(const QString & headName);

    void setDependsVector(const QVector<DependencyStruct *> & depsVector);

    void setDefaultSettings();

    void clear();

signals:
    void updated();

private:
    struct Impl;
    std::unique_ptr<Impl> d;

    void drawGraph(DependencyStruct * head);
    void drawObject(const DependencyStruct * object);
    void connectDepends(DependencyStruct * head);
    void drawHistory();

    void paintEvent(QPaintEvent * e);
    void mousePressEvent(QMouseEvent * e);
};

}

#endif // DEPENDENCYGRAPHWIDGET_H
