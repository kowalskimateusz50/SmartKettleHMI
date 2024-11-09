#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace mn::CppLinuxSerial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    //Adding title for widget
    QWidget::setWindowTitle("Serial Port Connection");

    //Set font colors and size
    QPalette TextPalette;
    QFont TextFont("Arial", 15);
    TextPalette.setColor(QPalette::WindowText, Qt::red);


    //Propagate palette style for
    ui->QLabelTemperatureDisplay->setPalette(TextPalette);
    ui->QLabelTemperatureDisplay->setFont(TextFont);


    //Set background
    QPixmap bkgnd(":/resources/img/Background2.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette ScreenPalette;
    ScreenPalette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(ScreenPalette);




    //Initialize serial port connection
    qDebug() << "\nSerial Port communication initialization: ";
    SerialPortComThread.InitSerialPortCom();

    //Start serial port listening thread
    SerialPortComThread.start();

    //Connect signals and slots
    connect(&SerialPortComThread,SIGNAL(SerialPortCom::TransmitTemperatureToDisplay(std::string)),this,SLOT(DisplayReceivedTemperature(std::string)));

    //Initialize Qlabel text display
    ui->QLabelTemperatureDisplay->setText("Hello temperature");

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





