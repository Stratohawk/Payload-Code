#include "DataLogger.h"
#include "Arduino.h"
#include <SPI.h>
#include <SD.h>

uint32_t sdBaud;
bool fileIsOpen = false;
int fileCount = 0;
File dataFile;

dLog::dLog( int chipSelectPin, uint32_t baudRate ){
  if (!SD.begin(chipSelectPin)) {
    Serial.println("Card failed, or not present");
  }
}

int openNewFile(){
    String fileName = "DTA";
  if( fileIsOpen ){
    return 1;
  }
  else {
    fileName += String(fileCount);
    dataFile = SD.open(fileName, FILE_WRITE);
    fileIsOpen = true;
    fileCount++;
    return 0;
  }
}

int writeToFile( String data ){
  if(!fileIsOpen){
    return 1;
  } else if(!dataFile){
    return 2;
  } else{
    dataFile.println(data);
    return 0;
  }
  
}

