#include "DataLogger.h"
#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

//values for file management
uint32_t sdBaud;
bool fileIsOpen = false;
int fileCount = 0;

File dataFile;

dLog::dLog( int chipSelectPin, uint32_t baudRate ){
  if (!SD.begin(chipSelectPin)) {
    Serial.println("Card failed, or not present");
  }
}
/*
int dLog::logGPS( float lattitude, float longitude){
  if(GPSLogCurIndex >= sizeof GPSLog[0]){
    return 1;
  }else{
    GPSLog[0][GPSLogCurIndex] = lattitude; //index 0 = lattitude
    GPSLog[1][GPSLogCurIndex] = longitude; //index 1 = longitude
    GPSLogCurIndex++;
    return 0;
  }
}

int dLog::logAltitude( int altd){
  if(AltLogCurIndex >= sizeof AltLog){
    return 1;
  }else{
    AltLog[AltLogCurIndex] = altd; //logs current altitude
    GPSLogCurIndex++;
    return 0;
  }
}
*/
int dLog::openFile(){
   String fileName = "DTA";
  if( fileIsOpen ){
    return 1;
  }
  else {
    fileName += String(fileCount);
    fileName += ".csv";
    dataFile = SD.open(fileName, FILE_WRITE);
    fileIsOpen = true;
    fileCount++;
    return 0;
  }
}



int dLog::closeFile(){
  if( !fileIsOpen ){
    return 1;
  }
  else if( !dataFile) {
    return 2;
  }else{
    dataFile.close();
    return 0;
  }
}

int dLog::writeToFile( String sTime, float lattitude, float longitude, int altd, float angX, float angY, float angZ){
  if(!fileIsOpen){
    return 1;
  } else if(!dataFile){
    return 2;
  } else{
    dataFile.println(sTime + "," + lattitude + "," + longitude + "," + altd + "," + angX + "," + angY + "," + angZ + ",");
    return 0;
  }
}

  int dLog::getFileCount(){
    return fileCount;
  }
  
  


