#ifndef SGPS
#define SGPS

#include "Arduino.h"
#include "StratoGPS.h"
#include <TinyGPS++.h>

class StGPS{
  public:
    //constructor
    StGPS( int Rx, int Tx, uint32_t baudRate );

    //methods
    void readStream();
    float getLat();
    float getLong();

  private:
    float longitude;
    float latitude;
    int RxPin, TxPin;
    uint32_t GPSBaud;
    bool isInit;

};
#endif
