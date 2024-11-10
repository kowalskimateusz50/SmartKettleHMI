#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QString>
#include <QDebug>
#include "SerialPortThread.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void DisplayReceivedTemperature(std::string Temperature);

signals:
    void startSerialPortThread(int n = 20);

private:
    Ui::MainWindow *ui;
    SerialPortThread serialPortThread; //Serial port com thread instance
    QThread* _thread = new QThread;

};
#endif // MAINWINDOW_H
