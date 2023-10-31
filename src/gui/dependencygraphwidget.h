#ifndef DEPENDENCYGRAPHWIDGET_H
#define DEPENDENCYGRAPHWIDGET_H

#include <QWidget>
#include <memory>

namespace Ui {
class DependencyGraphWidget;
}

class DependencyGraphWidget : public QWidget
{
    Q_OBJECT

public:
    explicit DependencyGraphWidget(QWidget *parent = 0);
    ~DependencyGraphWidget();

    void addDependency(const QString & who, const QVector<QString> & from);

    void draw();

    void clear();

private:
    Ui::DependencyGraphWidget *ui;

    struct Impl;
    std::unique_ptr<Impl> m_pImpl;
};

#endif // DEPENDENCYGRAPHWIDGET_H
