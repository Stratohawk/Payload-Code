#include "StratoGPS.h"
#include "Arduino.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int RxPin;
int TxPin;
uint32_t GPSBaud;
int latitude;
int longitude;
bool isInit = true;

StGPS::StGPS(int Rx, int Tx, uint32_t baudRate ){
  uint32_t GPSBaud = baudRate;
  RxPin = Rx;
  TxPin = Tx;
  isInit = true;
}

TinyGPSPlus gps;
SoftwareSerial ss(RxPin, TxPin);

void readStream(){
  if(isInit == true){
    ss.begin(GPSBaud);
    isInit = false;
  } //starts stream if first time through loop
  while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){      
      latitude = gps.location.lat();      
      longitude = gps.location.lng();
    } //stores new info if location is updated
  } //reads buffer if able 
} //persistent loop method

long getLat(){
  return latitude;
} //returns current value

long getLong(){
  return longitude;
} //returns current value

