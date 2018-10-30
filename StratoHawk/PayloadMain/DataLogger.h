#ifndef DL
#define DL


#include "Arduino.h"
#include "DataLogger.h"

class dLog {
  public:
    //constructor
    dLog( int chipSelectPin, uint32_t baudRate );

    //methods
    int openNewFile();
    int writeToFile( String data );

  private:
    uint32_t sdBaud;
    bool fileIsOpen;
    int fileCount;
};
#endif
