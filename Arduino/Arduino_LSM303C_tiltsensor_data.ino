// I2C interface by default
//
#include "Wire.h"
#include "SparkFunIMU.h"
#include "SparkFunLSM303C.h"
#include "LSM303CTypes.h"
#include <SoftwareSerial.h>

// Serial Port for the Campbell CR1000 Datalogger
SoftwareSerial CampbellSerial(8, 7); // RX, TX, an optional 3rd argument of 1 means TTL signals inverted

int SensorNum = 10000; // Sensor address number
int Wall = 1; // Prevent Spillover

// #define DEBUG 1 in SparkFunLSM303C.h turns on debugging statements
// Redefine to 0 to turn them off

LSM303C myIMU;

void setup()
{
  Serial.begin(9600);
  CampbellSerial.begin(9600);
  pinMode(3, OUTPUT);
  if (myIMU.begin() != IMU_SUCCESS)
  {
    Serial.println("Failed setup");
    while (1);
  }
}

void loop()
{
  digitalWrite(3, LOW);
  int CallSensorNum = 0;
  CallSensorNum = CampbellSerial.parseInt(); // Read in CR1000 command call
  if (CallSensorNum == SensorNum) { // Check if command call matches sensor address number
    digitalWrite(3, HIGH);
    delay(100);
    // Get all parameters from LSM303C
    // Sensor Number
    CampbellSerial.print(SensorNum);
    CampbellSerial.print(" ");
    // Acc Data
    CampbellSerial.print(myIMU.readAccelX(), 4);
    CampbellSerial.print(" ");
    CampbellSerial.print(myIMU.readAccelY(), 4);
    CampbellSerial.print(" ");
    CampbellSerial.print(myIMU.readAccelZ(), 4);
    CampbellSerial.print(" ");
    // Mag Data
    CampbellSerial.print(myIMU.readMagX(), 4);
    CampbellSerial.print(" ");
    CampbellSerial.print(myIMU.readMagY(), 4);
    CampbellSerial.print(" ");
    CampbellSerial.print(myIMU.readMagZ(), 4);
    CampbellSerial.print(" ");
    // Thermometer Data
    CampbellSerial.print(myIMU.readTempC(), 4);
    CampbellSerial.print(" ");
    CampbellSerial.println(myIMU.readTempF(), 4);
    CampbellSerial.print(" ");
    // Indicate end of string
    CampbellSerial.print(Wall);
    CampbellSerial.print(" ");
    CampbellSerial.print("!");
  }
}
