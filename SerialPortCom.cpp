#include "SerialPortCom.h"

//Thread execution
void SerialPortCom::run() {

    //while(true) {

    //QThread::msleep(100);
    for (int x = 0; x < 10; x++) {
        qDebug() << "\nReading";
        std::string readData = ReadFromPort();

        qDebug() << "\nReadData: " << readData;
    }

}

void SerialPortCom::InitSerialPortCom() {

    //Future defining from file
    serialPort.Initialize("/dev/ttyACM0", BaudRate::B_115200, NumDataBits::EIGHT, Parity::NONE, NumStopBits::ONE, HardwareFlowControl::ON, SoftwareFlowControl::OFF);
    serialPort.SetTimeout(1000); // Block when reading for 1000ms

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

