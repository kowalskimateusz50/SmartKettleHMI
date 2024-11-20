#include "SerialPortData.h"

SerialPortData::SerialPortData()
{
    //Initialize I/O data
    //Input Data (STM32 -> RPI)
    string iInputData = "";
    string iWatchDog = "";
    int iTemperatureReading = 0;
    int iOperationStatus = 0;
    int iErrorCode = 0;

    //Output data (RPI -> STM32)
    string oOutputData = "";
    string oWatchDog = "";
    int oTemperatureAdjustment = 0;
    int oStartRequest = 0;
    int oStopRequest = 0;
}

void SerialPortData::readInputData(string inputData)
{
    //Save input data into private variable
    iInputData = inputData;

    //debug input message
    qDebug() << "\nReceived: " << inputData;

    //Extract temperature from input data
    if(extractTemperatureReading())
    {
        qDebug() << "\n Temperature: " << iTemperatureReading << " 0c" << Qt::endl;
    }
    else
    {
        qDebug() << "\nError: Temperature reading failed" << Qt::endl;
    }

}

int SerialPortData::extractTemperatureReading()
{
    //Prefixes definition
    string tInputData = iInputData;
    string tPrefix = "Temperature:";
    char tEndChar = ';';

    //Get temperature reading
    iTemperatureReading = stof(extractDataFromString(tInputData, tPrefix, tEndChar));

    //Error handling
    if (iTemperatureReading > 0)
        return 1;
    else
        return 0;
}

int SerialPortData::findValueAfterPrefix(string iBaseString, string iSubString)
{

    int DiffChars;

    for (int i = 0; i <= iBaseString.length() - iSubString.length(); i++)
    {
        DiffChars = 0;

        for (int j = i; j < (i + iSubString.length()); j++)
        {
            if(iBaseString[j] != iSubString[j - i])
            {
                DiffChars++;
                break;
            }
        }
        if(DiffChars == 0)
        {
            return (i + iSubString.length());
        }

    }
    return 0;
}
