#include <LSM6DS3.h>
#include <Wire.h>
#include <bluemicro_hid.h> 

LSM6DS3 myIMU(I2C_MODE, 0x6A);

// Accumulators for smooth "sub-pixel" movement
float accX = 0;
float accY = 0;

void setup() {
  Serial.begin(115200);

  // Initialize HID (USB + BLE)
  bluemicro_hid.begin(); 

  // Initialize IMU
  if (myIMU.begin() != 0) {
    Serial.println("IMU Error!");
    while (1); 
  }
  Serial.println("IMU Ready. Move the board!");
}

void loop() {
  // 1. Read Gyro
  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();

  // 2. Add to Accumulator (Sensitivity: Lower 5.0 to 2.0 for faster mouse)
  // We add to a "bucket" (accX) until it overflows past 1.0
  accX += (-gx / 5.0);
  accY += (gy / 5.0);

  // 3. convert to Integer for Mouse
  int dx = (int)accX;
  int dy = (int)accY;

  // 4. Move ONLY if we have integer movement
  if (dx != 0 || dy != 0) {
    
    // Debugging: Print WHAT we are trying to send
    Serial.print("Gyro: "); Serial.print(gx);
    Serial.print(" | Sending Mouse: "); Serial.print(dx); Serial.print(", "); Serial.println(dy);

    bluemicro_hid.mouseMove(dx, dy);

    // Remove the moved amount from the bucket
    accX -= dx;
    accY -= dy;
  }

  delay(10);
}
