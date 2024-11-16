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
            //Communicate ready for receive data
            case 100:
            {
                //qDebug() << "\nCommunicate ready for read";
                WriteToPort("rd");
                //Wait some time
                QThread::msleep(100);
                SequenceStep = 200;
                break;
            }
            //Read data and display
            case 200:
            {
                //qDebug() << "\nReading data";
                readData = ReadFromPort();
                qDebug() << readData;

                if(readData.length() > 0)
                {
                    emit TransmitTemperatureToDisplay(readData); //Send temperature readings to GUI
                    //Reading data sucessfull
                    SequenceStep = 300;
                }
                else
                {
                    //Repeat reading data
                    SequenceStep = 0;
                }
                break;
            }
            //Comunicate ready for transmit data
            case 300:
            {
                //qDebug() << "\nCommunicate reeady for writing";
                WriteToPort("wr");
                //Wait some time
                QThread::msleep(100);
                SequenceStep = 400;
                break;
            }
            //Send data through serial port
            case 400:
            {
                std::string TempAdjust = "xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxTempAdjust:069;.";
                WriteToPort(TempAdjust);
                //Place for future data handshake
                SequenceStep = 0;
                QThread::msleep(100);
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

