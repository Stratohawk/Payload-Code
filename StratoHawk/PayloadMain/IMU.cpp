#include "IMU.h"
#include "Arduino.h"
#include <Wire.h>
#include <TimerOne.h>

#define    MPU9250_ADDRESS            0x68
#define    MAG_ADDRESS                0x0C

#define    GYRO_FULL_SCALE_250_DPS    0x00  
#define    GYRO_FULL_SCALE_500_DPS    0x08
#define    GYRO_FULL_SCALE_1000_DPS   0x10
#define    GYRO_FULL_SCALE_2000_DPS   0x18

#define    ACC_FULL_SCALE_2_G        0x00  
#define    ACC_FULL_SCALE_4_G        0x08
#define    ACC_FULL_SCALE_8_G        0x10
#define    ACC_FULL_SCALE_16_G       0x18

int timePrev = 0;
int timeCur = 0;
int delt_t = 0;
int count = 0;
bool imuIsInit = true;

float AccGX = 0;
float AccGY = 0;
float AccGZ = 0;

float angX = 0;
float angY = 0;
float angZ = 0;

// Initial time
volatile bool intFlag=false;

StIMU::StIMU(){
  //initialize();
}

// This function read Nbytes bytes from I2C device at address Address. 
// Put read bytes starting at register Register in the Data array. 
void StIMU::I2Cread(uint8_t Address, uint8_t Register, uint8_t Nbytes, uint8_t* Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.endTransmission();
  
  // Read Nbytes
  Wire.requestFrom(Address, Nbytes); 
  uint8_t index=0;
  while (Wire.available())
    Data[index++]=Wire.read();
}


// Write a byte (Data) in device (Address) at register (Register)
void StIMU::I2CwriteByte(uint8_t Address, uint8_t Register, uint8_t Data)
{
  // Set register address
  Wire.beginTransmission(Address);
  Wire.write(Register);
  Wire.write(Data);
  Wire.endTransmission();
}

// Initializations
void StIMU::initialize()
{
  // Arduino initializations
  //Wire.begin();
  
  // Set accelerometers low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,29,0x06);
  // Set gyroscope low pass filter at 5Hz
  I2CwriteByte(MPU9250_ADDRESS,26,0x06);
 
  
  // Configure gyroscope range
  I2CwriteByte(MPU9250_ADDRESS,27,GYRO_FULL_SCALE_1000_DPS);
  // Configure accelerometers range
  I2CwriteByte(MPU9250_ADDRESS,28,ACC_FULL_SCALE_4_G);
  
  Timer1.initialize(10000);         // initialize timer1, and set a 1/2 second period
  //Timer1.attachInterrupt(callback);  // attaches callback() as a timer overflow interrupt
  
}

void StIMU::callback()
{ 
  intFlag=true;
}

// Main loop, read and display data
void StIMU::runLoop()
{
  //while (!intFlag);
  intFlag=false;

  if(imuIsInit){
    imuIsInit = false;
  // Store initial time
  timePrev = millis();
  }
 
  // ____________________________________
  // :::  accelerometer and gyroscope ::: 

  // Read accelerometer and gyroscope
  uint8_t Buf[14];
  I2Cread(MPU9250_ADDRESS,0x3B,14,Buf);
  
  // Create 16 bits values from 8 bits data
  
  // Gyroscope
  int16_t gx=-(Buf[8]<<8 | Buf[9]);
  int16_t gy=-(Buf[10]<<8 | Buf[11]);
  int16_t gz=Buf[12]<<8 | Buf[13];
  

  // Gyroscope

timeCur = millis();
delt_t = timeCur - timePrev;

  AccGX = AccGX + (float) gx*delt_t/1000;
  AccGY = AccGY + (float) gy*delt_t/1000;
  AccGZ = AccGZ + (float) gz*delt_t/1000;

  angX = AccGX*90.0/2600;
  angY = AccGY*90.0/2600;
  angZ = AccGZ*90.0/2600;

 timePrev = timeCur;
}

float StIMU::getAngX() {
  return angX;
}

float StIMU::getAngY() {
  return angY;
}

float StIMU::getAngZ() {
  return angZ;
}
