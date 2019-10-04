#include <Wire.h>
#include "StratoGPS.h"
#include "DataLogger.h"
#include "Altimeter.h"
#include "IMU.h"

StAlt mAlt; //iic ports 2,3
StIMU mIMU;
StGPS mGPS(9, 8, 9600);
dLog mDataLogger(SS, 9600);

boolean loopIsInit = true;
int currentTimeStamp = 0, last10hzTimeStamp = 0, last1hzTimeStamp = 0, last2MTimeStamp = 0;

void setup() {
  Wire.begin();
  mAlt.start();
  Serial.begin(9600);
  mGPS.setup();
  mIMU.initialize();
  // put your setup code here, to run once:

  //TODO: configure XBee Transceiver
  //TODO: configure Sensor Package (gyro/accel)

  mDataLogger.openFile(); //opens first file
}

void loop() {
  if (loopIsInit) {
    loopIsInit = false;
    currentTimeStamp = millis();
    last10hzTimeStamp = currentTimeStamp;
    last1hzTimeStamp = currentTimeStamp;
    last2MTimeStamp = currentTimeStamp;
  }
  currentTimeStamp = millis();
  //Serial.println(currentTimeStamp);
  run10hz();
  run1hz();
  runEvery2Min();


}

void run10hz() {
  if ((currentTimeStamp - last10hzTimeStamp) >= 100) {
    //Serial.println("::10hz");
    last10hzTimeStamp = millis();

    mGPS.readStream();
    mIMU.runLoop();

  }
}

void run1hz() {
  if ((currentTimeStamp - last1hzTimeStamp) >= 1000) {
    //Serial.println("::1hz");

    last1hzTimeStamp = millis();


    String timer = mGPS.getTime();


    Serial.print("  Time: ");
    Serial.println( timer);
    Serial.print("  Lat: ");
    Serial.println(mGPS.getLat(), 6);
    Serial.print("  Lng: ");
    Serial.println(mGPS.getLong(), 6);
    Serial.print("  Alt: ");
    Serial.println(mAlt.getAltitude());

    Serial.print("  Angle X: ");
    Serial.println(mIMU.getAngX());
    Serial.print("  Angle Y: ");
    Serial.println(mIMU.getAngY());
    Serial.print("  Angle Z: ");
    Serial.println(mIMU.getAngZ());

    Serial.println();

    Serial.print("write to disk: ");

    //int m = mDataLogger.writeToFile("time", 0, 0, 0, 0, 0, 0);
    int m = mDataLogger.writeToFile(mGPS.getTime(), mGPS.getLat(), mGPS.getLong(), mAlt.getAltitude(), mIMU.getAngX(), mIMU.getAngY(), mIMU.getAngZ());

    Serial.println(m);


    Serial.println();



  }
}

void runEvery2Min() {
  if ((currentTimeStamp - last2MTimeStamp) >= 120000) {
    Serial.println("::2m");

    last2MTimeStamp = millis();

    Serial.print("closing file: ");
    Serial.println(mDataLogger.closeFile());

    Serial.print("opening file: ");
    Serial.println(mDataLogger.openFile());

  }
}
