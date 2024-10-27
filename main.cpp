#include "mainwindow.h"
#include <QApplication>
#include "SharedMutex.h"

//Define mutex for serial port
std::mutex SerialPortMutex;

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return a.exec();
}
