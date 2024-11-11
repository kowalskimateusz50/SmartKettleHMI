#include "SerialPortThread.h"

SerialPortThread::SerialPortThread()
{

}

void SerialPortThread::doWork(int n)
{
    //Initialize main sequence step variable
    int SequenceStep = 0;
    std::string readData = "";

    qDebug() << "\nStarting sequence of communication: ";

     //Non endless loop
    while(true)
    {
        switch (SequenceStep)
        {

            //Initialization step
            case 0:
            {
                //Clear read data
                readData == "";
                SequenceStep = 100;
                break;
            }
            //Communicate ready for receivers data
            case 100:
            {
                qDebug() << "\nWiriting listen status";
                WriteToPort("listetning");
                //Wait some time
                QThread::msleep(500);
                SequenceStep = 200;
                break;
            }
            //Read data and display
            case 200:
            {
                qDebug() << "\nReading data";
                readData = ReadFromPort();
                qDebug() << readData;
                emit TransmitTemperatureToDisplay(readData); //Send temperature readings to GUI
                SequenceStep = 300;
                break;
            }
            //Comunicate ready for transmit data
            case 300:
            {


                break;
            }
        }
    }
}

void SerialPortThread::InitSerialPortCom()
{

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

void SerialPortThread::WriteToPort(const std::string& data) {
    serialPort.Write(data);
}

std::string SerialPortThread::ReadFromPort() {
    std::string readData;
    serialPort.Read(readData);

    return readData;
}

SerialPortThread::~SerialPortThread() {
    serialPort.Close();
}

