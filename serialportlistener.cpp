#include "serialportlistener.h"

//Initialization of conection
SerialPortListener::SerialPortListener(){
    //serialPort("/dev/ttyACM0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, HardwareFlowControl::ON, SoftwareFlowControl::OFF);
    //serialPort.SetTimeout(1000); // Block when reading for 1000ms

    //qDebug() << "\nSerial port configured: ";
}

//Thread execution
void SerialPortListener::run() {

    //serialPort.Open();
    //QThread::msleep(100);

    qDebug() << "\nConnection Opened: ";
    qDebug() << "\nStarting listening for data: ";

    for(int i=0; i< 20; ++i) {
        qDebug() << i;
        QThread::msleep(1000);
    }


}
