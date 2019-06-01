#include "StratoGPS.h"
#include "DataLogger.h"
#include "Altimeter.h"
#include "IMU.h"

StAlt mAlt; //iic ports 2,3
StIMU mIMU;
StGPS mGPS(4, 3, 9600);
dLog mDataLogger(10,9600);

boolean loopIsInit = true;
int currentTimeStamp, last10hzTimeStamp, last1hzTimeStamp, last2MTimeStamp;

void setup() {
  // put your setup code here, to run once:

  //TODO: configure XBee Transceiver
  //TODO: configure Sensor Package (gyro/accel)
  
  mDataLogger.openFile(); //opens first file
}

void loop() {
  if(loopIsInit){
    loopIsInit = false;
    currentTimeStamp = millis();
    last10hzTimeStamp = currentTimeStamp;
    last1hzTimeStamp = currentTimeStamp;
    last2MTimeStamp = currentTimeStamp;
  }
  currentTimeStamp = millis();
  
  run10hz();
  run1hz();
  runEvery2Min();
  
  
}

void run10hz() {
  if((currentTimeStamp - last10hzTimeStamp) >= 100){

    last10hzTimeStamp = millis();
    
    mIMU.runLoop();
  
  }
}

void run1hz() {
  if((currentTimeStamp - last1hzTimeStamp) >= 1000){
    
    last1hzTimeStamp = millis();  
    
    mDataLogger.writeToFile(mGPS.getTime(), mGPS.getLat(), mGPS.getLong(), mAlt.getAltitude(), mIMU.getAngX(), mIMU.getAngY(), mIMU.getAngZ());
    
  }
}

void runEvery2Min() {
  if((currentTimeStamp - last2MTimeStamp) >= 12000){
    
    last2MTimeStamp = millis();  

    mDataLogger.closeFile();
    mDataLogger.openFile();
    
  }
}
