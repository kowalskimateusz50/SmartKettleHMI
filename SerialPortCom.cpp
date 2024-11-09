#include "SerialPortCom.h"
#include "mainwindow.h"

/* Class constructor
 *  Initialization of communication sequence variable
*/
SerialPortCom::SerialPortCom()
{
    int SequenceStep = 0;
}

//Thread execution
void SerialPortCom::run()
{

    //Non endless loop
    while(true)
    {
        switch (SequenceStep)
        {

            //Initialization step
            case 0:
                {
                    qDebug() << "\nStarting sequence of communication: ";
                    SequenceStep = 100;
                    break;
                }
            //Communicate ready for data read status
            case 100:
                {
                    qDebug() << "\nWiriting listen status";
                    WriteToPort("listetning");
                    //Wait some time
                    QThread::msleep(5000);
                    SequenceStep = 200;
                    break;
                }
            //Read data and display
            case 200:
                {
                    qDebug() << "\nReading data";
                    std::string readData = ReadFromPort();
                    qDebug() << readData;
                    emit TransmitTemperatureToDisplay(readData); //Send temperature readings to GUI
                    SequenceStep = 100;
                    break;
                }
        }
    }
}

void SerialPortCom::InitSerialPortCom()
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

void SerialPortCom::WriteToPort(const std::string& data) {
    serialPort.Write(data);
}

std::string SerialPortCom::ReadFromPort() {
    std::string readData;
    serialPort.Read(readData);

    return readData;
}

void SerialPortCom::TransmitTemperatureToDisplay(std::string Temperature) {

}

SerialPortCom::~SerialPortCom() {
    serialPort.Close();
}




