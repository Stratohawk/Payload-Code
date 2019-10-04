#ifndef SGPS
#define SGPS

#include "Arduino.h"
#include "StratoGPS.h"
#include <TinyGPS++.h>
#include <SoftwareSerial.h>

class StGPS{
  public:
    //constructor
    StGPS( int Rx, int Tx, uint32_t baudRate );

    //methods
    void setup();
    void readStream();
    float getLat();
    float getLong();
    String getTime();
    int getSatellites();

  private:

    float longitude;
    float latitude;
    int RxPin, TxPin;
    uint32_t GPSBaud;
    bool isInit;

};
#endif
