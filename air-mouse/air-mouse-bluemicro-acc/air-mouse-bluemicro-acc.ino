#include <LSM6DS3.h>
#include <Wire.h>
#include <bluemicro_hid.h> 

LSM6DS3 myIMU(I2C_MODE, 0x6A);

// Accumulators for smoother movement
float accX = 0;
float accY = 0;

void setup() {
  // Initialize HID (USB + BLE)
  // This automatically sets up the USB stack if plugged in
  bluemicro_hid.begin(); 

  // Initialize IMU
  if (myIMU.begin() != 0) {
    // If IMU fails, we can't do anything, but let's not freeze 
    // so we can still see if USB connects.
  }
}

void loop() {
  // 1. Read Gyro
  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();

  // 2. Accumulate Movement (Sensitivity: 5.0)
  accX += (-gx / 5.0);
  accY += (gy / 5.0);

  int dx = (int)accX;
  int dy = (int)accY;

  // 3. Queue the Mouse Movement
  if (dx != 0 || dy != 0) {
    bluemicro_hid.mouseMove(dx, dy);
    
    accX -= dx;
    accY -= dy;
  }

  // 4. CRITICAL FIX: Send the data!
  // CONNECTION_MODE_AUTO tells it to use USB if plugged in, otherwise BLE.
  bluemicro_hid.processQueues(CONNECTION_MODE_AUTO);

  delay(10);
}
