#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include "SerialPortCom.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

public slots:
    void DisplayReceivedTemperature(std::string Temperature);

private:
    Ui::MainWindow *ui;
    SerialPortCom SerialPortComThread; //


};
#endif // MAINWINDOW_H
