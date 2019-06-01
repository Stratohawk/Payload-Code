#ifndef IM
#define IM

#include "IMU.h"
#include "Arduino.h"

#include <Wire.h>
#include <TimerOne.h>

class StIMU{
  public:
    //constructor
    StIMU();

    //methods
    void runLoop();
    float getAngX();
    float getAngY();
    float getAngZ();
    void callback();
  void initialize();
  void I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data);
  void I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data);

  private:
int timePrev = 0;
int timeCur = 0;
int delt_t = 0;
int count = 0;
bool isInit = true;

float AccGX = 0;
float AccGY = 0;
float AccGZ = 0;

float angX = 0;
float angY = 0;
float angZ = 0;


};
#endif
