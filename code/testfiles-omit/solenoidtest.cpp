// Solenoid test (works) 
#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>

#define I2C_SDA_PIN 21
#define I2C_SCL_PIN 22

#define SOLENOID_CHANNEL 0   // CH0 on PCA9685 -> ULN2803 input 1 -> solenoid 1

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Solenoid test starting");
  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);

  if (!pwm.begin()) {
    Serial.println("PCA9685 not detected");
    while (1) delay(1000);
  }
  pwm.setPWMFreq(1000);
  pwm.setPWM(SOLENOID_CHANNEL, 0, 0);
  Serial.println("PCA9685 initialized");
}

void loop() {
  Serial.println("Solenoid on");
  pwm.setPWM(SOLENOID_CHANNEL, 0, 4095);  // fully on
  delay(1000);

  Serial.println("Solenoid off");
  pwm.setPWM(SOLENOID_CHANNEL, 0, 0);     // fully off
  delay(1000);
}
