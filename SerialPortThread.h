#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDebug>
#include "SerialPort.h"

using namespace mn::CppLinuxSerial;


class SerialPortThread : public QObject
{
    Q_OBJECT
public:
    SerialPortThread();

    void InitSerialPortCom();

    void WriteToPort(const std::string& data);

    std::string ReadFromPort();

    ~SerialPortThread();

public slots:
    void doWork(int n = 20); //Thread execution
signals:
    void TransmitTemperatureToDisplay(std::string Temperature);

private:
    SerialPort serialPort;
    int SequenceStep;

};

#endif // SERIALPORTTHREAD_H
