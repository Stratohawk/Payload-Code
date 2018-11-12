#ifndef ATL
#define ATL

#include "Arduino.h"
#include "Altimeter.h"

#include <Wire.h>

class StAlt{
  public:
    //constructor
    StAlt( int SDA, int SCL);

    //methods
    int getAltitude();
    int start();

  private:
    int SDA, SCL;
    bool altIsInit;

};
#endif
