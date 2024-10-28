#include "SerialPortCom.h"

//Thread execution
void SerialPortCom::run() {

    while(true) {
        qDebug() << "\nReading";
        std::string readData = ReadFromPort();

        qDebug() << "\nReadData: " << readData;

        QThread::msleep(1000);
    }

}

void SerialPortCom::InitSerialPortCom() {

    /*Future defining from file
     * Use "/dev/ttyACM0" for Linux Desktop running
     * Use "/dev/ttyS0 for RPI running
    */
    serialPort.Initialize("/dev/ttyS0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, HardwareFlowControl::ON, SoftwareFlowControl::OFF);
    serialPort.SetTimeout(100); // Block when reading for 100ms

    //Open port com
    serialPort.Open();

    qDebug() << "\nPort communication opened: ";

}

void SerialPortCom::WriteToPort(const std::string& data) {
    serialPort.Write(data);
}

std::string SerialPortCom::ReadFromPort() {
    std::string readData;
    serialPort.Read(readData);

    return readData;
}

SerialPortCom::~SerialPortCom() {
    serialPort.Close();
}

