#include <LSM6DS3.h>
#include <Wire.h>
#include <bluemicro_hid.h>
//some code snippet: techiesms
//Create an instance of class LSM6DS3
LSM6DS3 myIMU(I2C_MODE, 0x6A);    //I2C device address 0x6A

//Bluetooth : WIP
// Define pins : WIP
// LED for debugging (Blue LED on Xiao nRF52)
const int LED_PIN = LED_BLUE;
// for buttons


void setup() {
  Serial.begin(115200);

  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // LED Off (HIGH is off on Xiao)

  //Check IMU health
  if (myIMU.begin() != 0) {
    Serial.println("IMU error");
    // Blink fast forever if IMU fails
    while (1) {
      digitalWrite(LED_PIN, !digitalRead(LED_PIN));
      delay(100);
    }
  } 
  Serial.println("IMU ready");

  //init BLE: WIP
  bluemicro_hid.begin();

  // Check BLE health
  Serial.println("BLE ready, Connect to ");
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
    bluemicro_hid.mouseMove(dx,dy);
  }

  //leftclick : WIP
  delay (10);
  
}

