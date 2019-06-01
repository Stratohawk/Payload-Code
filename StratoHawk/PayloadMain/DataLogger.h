#ifndef DL
#define DL


#include "Arduino.h"
#include "DataLogger.h"

class dLog {
  public:
    //constructor
    dLog( int chipSelectPin, uint32_t baudRate );

    //methods
    int writeToFile( String sTime, float lattitude, float longitude, int altd, float angX, float angY, float angZ);
    int getFileCount();
    int openFile();
    int closeFile();

  private:
    uint32_t sdBaud;
    bool fileIsOpen;
    int fileCount;
};
#endif
