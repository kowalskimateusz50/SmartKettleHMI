#ifndef SERIALPORTDATA_H
#define SERIALPORTDATA_H

#include <QDebug>
#include <string>


using namespace std;

class SerialPortData
{

private:

    //Input Data (STM32 -> RPI)
    string iInputData;
    string iWatchDog;
    int iTemperatureReading;
    int iOperationStatus;
    int iErrorCode;

    //Output data (RPI -> STM32)
    string oOutputData;
    string oWatchDog;
    int TemperatureAdjustment;
    int StartRequest;
    int StopRequest;


public:
    SerialPortData();

};

#endif // SERIALPORTDATA_H
