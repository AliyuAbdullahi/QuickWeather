#include "ui/mainwindow.h"
#include <QtDebug>
#include <QString>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;

    w.show();

    qDebug() << qVersion();
    return a.exec();
}
