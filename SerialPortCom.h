#ifndef SERIALPORTCOM_H
#define SERIALPORTCOM_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include "SerialPort.h"
//#include "mainwindow.h"

using namespace mn::CppLinuxSerial;

class SerialPortCom : public QThread  {

public:
    SerialPortCom();

    void InitSerialPortCom();

    void WriteToPort(const std::string& data);

    std::string ReadFromPort();

    ~SerialPortCom();

private:
    SerialPort serialPort;
    int SequenceStep;

protected:
    //QThread interface
    void run();
signals:
    void TransmitTemperatureToDisplay(std::string Temperature);
};

#endif // SERIALPORTCOM_H
