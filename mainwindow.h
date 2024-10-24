#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <QDebug>
#include "serialportlistener.h"

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

    void on_SendPushButton_clicked();
    void on_DisconnectPushButton_clicked();
    void on_ConnectPushButton_clicked();
    void on_ClearPushButton_clicked();

private:
    Ui::MainWindow *ui;
    SerialPortListener SerialPortListening;



};
#endif // MAINWINDOW_H
