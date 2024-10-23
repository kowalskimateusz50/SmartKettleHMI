#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "SerialPort.hpp"

using namespace mn::CppLinuxSerial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Adding title for widget
    QWidget::setWindowTitle("Serial Port Connection");

    //Set font colors
    QPalette sample_palette;
    sample_palette.setColor(QPalette::WindowText, Qt::red);


    //Propagate palette style for
    ui->SendMessageLabel->setPalette(sample_palette);
    ui->ReceivedMessageLabel->setPalette(sample_palette);
    ui->ConnectLabel->setPalette(sample_palette);
    ui->StatusLabel->setPalette(sample_palette);
    ui->DisconnectLabel->setPalette(sample_palette);
    ui->DisconnectLabel->setPalette(sample_palette);

    //Set background
    QPixmap bkgnd("/home/mati/Desktop/QtProjects/KettleHMIDesktop/Graphics/Background2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    //Initialize serial port
    SerialPort serialPort("/dev/ttyACM0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, HardwareFlowControl::ON, SoftwareFlowControl::OFF);
    serialPort.SetTimeout(1000); // Block when reading for 1000ms


}

MainWindow::~MainWindow()
{

    delete ui;
}


//Disconnet button
void MainWindow::on_DisconnectPushButton_clicked()
{

}

//Connect Button
void MainWindow::on_ConnectPushButton_clicked()
{

}

//Send comment
void MainWindow::on_SendPushButton_clicked()
{

}


void MainWindow::on_ClearPushButton_clicked()
{
    ui->ReceivedMessageOutput->clear();
}
