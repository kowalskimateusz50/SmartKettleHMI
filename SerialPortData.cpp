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
    //Fame overview
    //STM32 -> RPI "TEMPERATURE:XXXXXXX;STATUS:XXX;ERRORCODE:XXX;."

    //Save input data into private variable
    iInputData = inputData;

    //debug input message
    //qDebug() << "\nReceived: " << iInputData;

    //Extract temperature from input data
    if(extractTemperatureReading())
    {
        //qDebug() << "\n Temperature: " << iTemperatureReading << " 0c" << Qt::endl;
        emit TransmitTemperatureToDisplay(iTemperatureReading); //Send temperature readings to GUI
        //emit TransmitTemperatureToDisplay(iTemperatureReading); //Send temperature readings to GUI
    }
    else
    {
        qDebug() << "\nError: Temperature reading failed" << Qt::endl;
    }

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

string SerialPortData::extractDataFromString(string iInputData, string iPrefix, char iEndChar)
{
    string RetString = "";

    for (int i = findValueAfterPrefix(iInputData, iPrefix); iInputData[i] != iEndChar ; i++)
    {
        RetString += iInputData[i];
    }

    return RetString;xxsawdwdawa
}

int SerialPortData::extractTemperatureReading()
{
    //Prefixes definition
    string tInputData = iInputData;
    string tPrefix = "Temperature:";
    char tEndChar = ';';

    qDebug() << "\nTemperature: " << extractDataFromString(tInputData, tPrefix, tEndChar) << Qt::endl;

    //Get temperature reading
    iTemperatureReading = stof(extractDataFromString(tInputData, tPrefix, tEndChar));

    if (iTemperatureReading > 0)
        return 1;
    else
        return 0;
}

/* Methods for creating output data frame */

string SerialPortData::getOutputData()
{
    //Frame overview RPI -> STM32 "TEMPADJUST:XXX;STARTREQ:X;STOPREQ:X;."
    //Initialize collective string
    oOutputData = "";
    //Temperature heating setpoint
    oOutputData += "TEMPADJUST:" + std::to_string(oTemperatureAdjustment) + ";";
    //Start request
    oOutputData += "STARTREQ:" + std::to_string(oStartRequest) + ";";
    //Stop request
    oOutputData += "STOPREQ:" + std::to_string(oStopRequest) + ";";
    //Add fram-ending sign
    oOutputData += ".";

    return oOutputData;
}

