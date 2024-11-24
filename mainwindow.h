#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QThread>
#include <QString>
#include <QDebug>
#include <QPixmap>
#include "SerialPortThread.h"
#include "SerialPortData.h"

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
    void DisplayReceivedTemperature(float Temperature);

    void on_pushButtonSave_clicked();

signals:
    void startSerialPortThread();

private:

    Ui::MainWindow   *ui;
    SerialPortData* serialPortData = new SerialPortData;
    SerialPortThread serialPortThread;
    QThread* _thread = new QThread;

    void setSylesSettings();
    void handlingThreads();
    void signalsAndSlotsConnecting();

};
#endif // MAINWINDOW_H
