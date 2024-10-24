#ifndef SERIALPORTLISTENER_H
#define SERIALPORTLISTENER_H

#include <QObject>
#include <QThread>
#include <QDebug>
#include "SerialPort.hpp"

using namespace mn::CppLinuxSerial;

class SerialPortListener : public QThread
{
    Q_OBJECT
public:
    SerialPortListener();

private:
    SerialPort serialPort;

protected:
    //QThread interface
    void run();
};

#endif // SERIALPORTLISTENER_H
