#ifndef SERIALPORTCOM_H
#define SERIALPORTCOM_H

#include <QObject>
#include <QThread>
#include <QMutex>
#include <QDebug>
#include <iostream>
#include "SerialPort.h"

using namespace mn::CppLinuxSerial;

class SerialPortCom : public QThread {

public:

    void InitSerialPortCom();

    void WriteToPort(const std::string& data);

    std::string ReadFromPort();

    ~SerialPortCom();

private:
    SerialPort serialPort;

protected:
    //QThread interface
    void run();

};

#endif // SERIALPORTCOM_H
