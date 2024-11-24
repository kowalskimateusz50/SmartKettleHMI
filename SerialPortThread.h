#ifndef SERIALPORTTHREAD_H
#define SERIALPORTTHREAD_H

#include <QObject>
#include <QDebug>
#include <QThread>
#include <QDebug>
#include "SerialPort.h"
#include "SerialPortData.h"

using namespace mn::CppLinuxSerial;


class SerialPortThread : public QObject
{
    Q_OBJECT

public:
    SerialPortThread();

    void InitSerialPortCom();

    void WriteToPort(const std::string& data);

    std::string ReadFromPort();

    void GetDataObject(SerialPortData* iSerialPortData);

    ~SerialPortThread();

public slots:
    void doWork(); //Thread execution

private:
    SerialPort serialPort;
    int SequenceStep;
    SerialPortData* _serialPortData;

};

#endif // SERIALPORTTHREAD_H
