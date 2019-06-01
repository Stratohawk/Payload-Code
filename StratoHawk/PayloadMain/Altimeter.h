#ifndef ATL
#define ATL

#include "Arduino.h"
#include "Altimeter.h"

#include <Wire.h>
#include <SparkFunMPL3115A2.h>

class StAlt{
  public:
    //constructor
    StAlt();

    //methods
    int getAltitude();
    int start();

  private:

};
#endif
