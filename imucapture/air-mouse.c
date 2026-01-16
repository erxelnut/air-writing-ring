#include <LSM6DS3.h>
#include <Wire.h>


//some code snippet: techiesms
//Create an instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);    //I2C device address 0x6A

//Bluetooth : WIP

// Define pins : WIP
// for buttons


void setup() {
  Serial.begin(9600);
  while (!Serial);

  //Check IMU health
  if (myIMU.begin() != 0) {
    Serial.println("IMU error");
    while (1)
	    ;
  } 
  Serial.println("IMU ready");

  //init BLE: WIP

  // Check BLE health
  Serial.println("BLE ready, Connect to ")
}

void loop() {
  // BLE check and blink: WIP

  // Read Gyro 
  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();
  float gz = myIMU.readFloatGyroZ();

  // Speed of Cursor (10 -> 2)
  float vx = -gx/ 5.0;
  float vy = gy/ 5.0;

  // flitering
  if (abs(vx) > 0.5 || abs(vy) > 0.5) {
    int8_t dx = (int8_t)vx;
    int8_t dy = (int8_t)vy;
    // move mouse: WIP
    blehid.mouseMove(dx,dy);
  }

  //leftclick : WIP
  delay (10);
  
}
