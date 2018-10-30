#include "StratoGPS.h"
#include "DataLogger.h"

StGPS payloadGPS(4, 3, 9600);
dLog payloadDataLogger(10, 9600);

int currentTimeStamp, last10hzTimeStamp, last1hzTimeStamp, last1PMTimeStamp;

void setup() {
  // put your setup code here, to run once:

  //TODO: configure XBee Transceiver
  //TODO: start data recorder
  //TODO: configure Sensor Package (gyro/accel/altimeter)

}

void loop() {
  
  run10hz();
  run1hz();
  run1PM();
  
  currentTimeStamp = millis();
  
}

void run10hz() {
  if((currentTimeStamp - last10hzTimeStamp) >= 100){
  
    last10hzTimeStamp = millis();
  }
}

void run1hz() {
  if((currentTimeStamp - last1hzTimeStamp) >= 1000){

    

    
    last1hzTimeStamp = millis();  
  }
}

void run1PM() {
  if((currentTimeStamp - last1PMTimeStamp) >= 6000){
    
    last1PMTimeStamp = millis();  
  }
}
