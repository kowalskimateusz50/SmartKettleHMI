#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace mn::CppLinuxSerial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Thread connecting
    connect(this, &MainWindow::startSerialPortThread, &serialPortThread, &SerialPortThread::doWork);
    serialPortThread.moveToThread(_thread);
    _thread->start();

    //Functional connecting
    connect(&serialPortThread, &SerialPortThread::TransmitTemperatureToDisplay, this, &MainWindow::DisplayReceivedTemperature);

    //Adding title for widget
    QWidget::setWindowTitle("Serial Port Connection");

    //Set font colors and size
    QPalette TextPalette;
    QFont TextFont("Arial", 15);
    TextPalette.setColor(QPalette::WindowText, Qt::red);

    //Propagate palette style for
    ui->QLabelTemperatureDisplay->setPalette(TextPalette);
    ui->QLabelTemperatureDisplay->setFont(TextFont);


    //Set background settings
    QPixmap bkgnd(":/resources/img/Background2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette ScreenPalette;
    ScreenPalette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(ScreenPalette);

    //Initialize serial port connection
    qDebug() << "\nSerial Port communication initialization: ";
    serialPortThread.InitSerialPortCom();

    //Initialize Qlabel text display
    ui->QLabelTemperatureDisplay->setText("Hello temperature");


    qDebug() << "\n Starting thread: ";
    emit startSerialPortThread();
}


void MainWindow::DisplayReceivedTemperature(std::string Temperature)
{
    qDebug() << "\nTemperature write slot activated: ";

    QString DisplayTemperature = QString::fromStdString(Temperature);
    //Display temperature on the screen
    ui->QLabelTemperatureDisplay->setText(DisplayTemperature);
}

MainWindow::~MainWindow()
{
    delete ui;
}





