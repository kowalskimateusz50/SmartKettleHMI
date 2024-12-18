#ifndef SERIALPORTDATA_H
#define SERIALPORTDATA_H

#include <QDebug>
#include <QObject>
#include <string>
#include <iomanip>


using namespace std;

class SerialPortData : public QObject
{
    Q_OBJECT

private:

    /* Input Data (STM32 -> RPI) */
    string iInputData;

    string iWatchDog;
    float iTemperatureReading;
    int iOperationStatus;
    int iErrorCode;

    /* Output data (RPI -> STM32) */
    string oOutputData;

    string oWatchDog;
    int oTemperatureAdjustment;
    int oStartRequest;
    int oStopRequest;

public:

    SerialPortData();

    /* Methods for reading input data frame */
    void readInputData(string InputData);
    int extractTemperatureReading();
    int findValueAfterPrefix(string iBaseString, string iSubString);
    string extractDataFromString(string iInputData, string iPrefix, char iEndChar);

    /* Methods for creating output data frame */
    string getOutputData();

signals:
    void TransmitTemperatureToDisplay(float Temperature);
};

#endif // SERIALPORTDATA_H
