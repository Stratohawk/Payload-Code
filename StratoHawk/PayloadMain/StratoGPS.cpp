#include "StratoGPS.h"
#include "Arduino.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

int RxPin = 8;
int TxPin = 9;
//uint32_t GPSBaud;
double latitude = 0.0;
double longitude = 0.0;
bool isInit = true;

static const int RXPin = 9, TXPin = 8; //****PORT NUMBERS****
static const uint32_t GPSBaud = 9600;

// The TinyGPS++ object
TinyGPSPlus gps;

// The serial connection to the GPS device
SoftwareSerial ss(RXPin, TXPin);

StGPS::StGPS(int Rx, int Tx, uint32_t baudRate ) {
  //GPSBaud = baudRate;
  RxPin = Rx;
  TxPin = Tx;
  isInit = true;
  Serial.println("init");
  ss.begin(GPSBaud);
}

void StGPS::setup() {
    Serial.println("init");
    ss.begin(9600);
    isInit = false;
  } //starts stream if first time through loop


void StGPS::readStream() {
      while (ss.available() > 0){
    gps.encode(ss.read());
    if (gps.location.isUpdated()){
      /*Serial.print("Latitude= "); 
      Serial.print(gps.location.lat(), 6);
      Serial.print(" Longitude= "); 
      Serial.println(gps.location.lng(), 6);
*/
      latitude = (gps.location.lat());
      longitude = (gps.location.lng());
    }
  }
} //persistent loop method

float StGPS::getLat() {
  return latitude;
} //returns current value

float StGPS::getLong() {
  return longitude;
} //returns current value

String StGPS::getTime()
{
  if (!gps.time.isValid())
  {
    return "*****************";
  }
  else
  {
    char sz[32];
    sprintf(sz, "%02d:%02d:%02d ", gps.time.hour(), gps.time.minute(), gps.time.second());

    
    return sz;
  }
}

int StGPS::getSatellites()
{
  if (!gps.satellites.isValid())
  {
    return -1;
  }
  else
  {
    return gps.satellites.value();
  }

}
