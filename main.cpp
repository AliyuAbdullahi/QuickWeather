#include "ui/mainwindow.h"
#include <QtDebug>
#include <QString>

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    qDebug() << "Qt Version: " << qVersion();

    MainWindow w;

    w.show();


    return a.exec();
}
