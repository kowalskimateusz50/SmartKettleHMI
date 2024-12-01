#include "mainwindow.h"
#include "ui_mainwindow.h"

using namespace mn::CppLinuxSerial;

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    signalsAndSlotsConnecting();

    setSylesSettings();

    handlingThreads();
}


void MainWindow::DisplayReceivedTemperature(float Temperature)
{
    //qDebug() << "\nTemperature write slot activated: ";

    QString DisplayTemperature;
    QTextStream DisplayTemperatureStream(&DisplayTemperature);
    DisplayTemperatureStream << QString::number(Temperature, 'f', 2) << " Oc";
    //Display temperature on the screen
    ui->qlabelTemperatureDisplay->setText(DisplayTemperature);
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButtonSave_clicked()
{

}

/* Section for setting up appearance of UI */

void MainWindow::setSylesSettings()
{
    //Adding title for widget
    QWidget::setWindowTitle("Smart kettle HMI");

    //Define fonts and palettss
    QPalette TextPalette;
    QPalette HeaderPalette;
    QFont HeaderFont("Arial", 26, QFont::Black);
    QFont TextFont("Arial", 20, QFont::Normal);

    TextPalette.setColor(QPalette::WindowText, QColor::fromRgb(255, 170, 0));
    HeaderPalette.setColor(QPalette::WindowText, QColor::fromRgb(51, 204, 51));

    //Propagate style for texts
    ui->qlabelTemperatureDisplayText->setPalette(TextPalette);
    ui->qlabelTemperatureDisplayText->setFont(TextFont);

    ui->textEditTemperatureAdjust->setPalette(TextPalette);
    ui->textEditTemperatureAdjust->setFont(TextFont);

    ui->qlabelTemperatureAdjustText->setPalette(TextPalette);
    ui->qlabelTemperatureAdjustText->setFont(TextFont);

    ui->pushButtonSave->setStyleSheet("QPushButton:enabled { background-color: rgb(153, 255, 153); }\n");
    ui->pushButtonSave->setFont(TextFont);

    ui->textEditTemperatureAdjust->setStyleSheet("background-color: rgb(51, 204, 255);");

    ui->qlabelTemperatureDisplay->setPalette(TextPalette);
    ui->qlabelTemperatureDisplay->setFont(TextFont);

    //Propagate style for headers
    ui->qlabelSettings->setPalette(HeaderPalette);
    ui->qlabelSettings->setFont(HeaderFont);

    ui->qlabelActualReadings->setPalette(HeaderPalette);
    ui->qlabelActualReadings->setFont(HeaderFont);

    //Set background settings
    QPixmap bkgnd(":/resources/img/Background.jpg");
    bkgnd = bkgnd.scaled(this->size(), Qt::IgnoreAspectRatio);
    QPalette ScreenPalette;
    ScreenPalette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(ScreenPalette);

    //Display termometer icons
    QPixmap termometerIcon(":/resources/img/thermometer.png");
    ui->qlabelTemperatureAdjustPic->setPixmap(termometerIcon.scaled(ui->qlabelTemperatureAdjustPic->width(),ui->qlabelTemperatureAdjustPic->height(),Qt::KeepAspectRatio));
    ui->qlabelTemperatureDisplayPic ->setPixmap(termometerIcon.scaled(ui->qlabelTemperatureDisplayPic->width(),ui->qlabelTemperatureDisplayPic->height(),Qt::KeepAspectRatio));

}

void MainWindow::handlingThreads()
{
    //Thread connecting
    connect(this, &MainWindow::startSerialPortThread, &serialPortThread, &SerialPortThread::doWork);
    serialPortThread.moveToThread(_thread);
    _thread->start();

    serialPortThread.GetDataObject(serialPortData);

    //Initialize serial port connection
    qDebug() << "\nSerial Port communication initialization: ";
    serialPortThread.InitSerialPortCom();

    qDebug() << "\n Starting thread: ";
    emit startSerialPortThread();
}

void MainWindow::signalsAndSlotsConnecting()
{

    //Connecting temperature display signal -> slot
    connect(serialPortData, &SerialPortData::TransmitTemperatureToDisplay, this, &MainWindow::DisplayReceivedTemperature);

}



