#ifndef DL
#define DL


#include "Arduino.h"
#include "DataLogger.h"

class dLog {
  public:
    //constructor
    dLog( int chipSelectPin, uint32_t baudRate );

    //methods
    int writeToFile( float lattitude, float longitude, int altd, float angX, float angY, float angZ);
    int getFileCount();

  private:
    uint32_t sdBaud;
    bool fileIsOpen;
    int fileCount;
};
#endif
