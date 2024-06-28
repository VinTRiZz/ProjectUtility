#include "gui/mainwindow.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();

    w.setBasePath(QApplication::applicationDirPath());
    w.init();

    return a.exec();
}
