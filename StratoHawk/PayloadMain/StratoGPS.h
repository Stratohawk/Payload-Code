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
    long getLat();
    long getLong();

  private:
    long longitude;
    long latitude;
    int RxPin, TxPin;
    uint32_t GPSBaud;
    bool isInit;

};
#endif
