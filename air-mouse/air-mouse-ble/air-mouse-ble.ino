#include <LSM6DS3.h>
#include <Wire.h>
#include <Adafruit_TinyUSB.h> // The Engine
#include <Mouse.h>            // The Steering Wheel

// IMU Setup
LSM6DS3 myIMU(I2C_MODE, 0x6A);
const int LED_PIN = LED_BLUE; 

void setup() {
  Serial.begin(115200);
  
  pinMode(LED_PIN, OUTPUT);
  digitalWrite(LED_PIN, HIGH); // Off

  // 1. Initialize IMU
  if (myIMU.begin() != 0) {
    Serial.println("IMU error");
    while (1) { // Fast panic blink
        digitalWrite(LED_PIN, !digitalRead(LED_PIN)); 
        delay(50); 
    }
  }
  Serial.println("IMU ready");

  // 2. Initialize USB Mouse
  Mouse.begin(); 
  Serial.println("Mouse ready");
}

void loop() {
  // Read Gyro
  float gx = myIMU.readFloatGyroX();
  float gy = myIMU.readFloatGyroY();

  // Print raw values to Serial Monitor for debugging
  // (Remove these lines later to make it smoother)
  Serial.print("X: "); Serial.print(gx);
  Serial.print(" Y: "); Serial.println(gy);

  // Movement Logic
  float vx = -gx / 5.0; 
  float vy = gy / 5.0;

  if (abs(vx) > 1.0 || abs(vy) > 1.0) {
    digitalWrite(LED_PIN, LOW); // LED ON when moving
    Mouse.move((int)vx, (int)vy);
  } else {
    digitalWrite(LED_PIN, HIGH); // LED OFF when still
  }

  delay(10);
}
