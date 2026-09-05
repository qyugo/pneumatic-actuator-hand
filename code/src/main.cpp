// Four Actuators (button controlled)

#include <Arduino.h>
#include <Wire.h>
#include <Adafruit_PWMServoDriver.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"

// ---------- Pin assignments ----------
#define I2C_SDA_PIN            21
#define I2C_SCL_PIN            22
#define COMPRESSOR_MOSFET_PIN  26   // drives relay coil via IRLZ44N
#define PRESSURE_ADC_CHANNEL   ADC1_CHANNEL_6  // GPIO34

//button assignments
#define MANUAL_BUTTON_PIN 27
#define MANUAL_SOLENOID_CHANNEL 0 

#define MANUAL_BUTTON_PIN_2 14
#define MANUAL_SOLENOID_CHANNEL_2 1

#define MANUAL_BUTTON_PIN_3 25
#define MANUAL_SOLENOID_CHANNEL_3 2

#define MANUAL_BUTTON_PIN_4 33
#define MANUAL_SOLENOID_CHANNEL_4 3

// ADC configuration
#define ADC_ATTEN  ADC_ATTEN_DB_11   // full ~0-3.3V range
#define ADC_WIDTH  ADC_WIDTH_BIT_12  // 0-4095
esp_adc_cal_characteristics_t adcChars;

// Voltage divider 10k->signal, 20k->GND)
const float DIVIDER_RATIO = 20000.0 / (10000.0 + 20000.0);  // 0.667

// Transducer config: 5-16VDC supply, 0.5-4.5V output, 0-150 PSI
const float TRANSDUCER_MIN_V = 0.5;
const float TRANSDUCER_MAX_V = 4.5;
const float MAX_PSI = 150.0;

// Transducer offset (check at 0 psi)
float PSI_OFFSET = 0.0;

// Compressor activation threshold (EDIT AS NEEDED, for specific McKibben start-up strength)
const float PRESSURE_LOW_PSI  = 8.0;
const float PRESSURE_HIGH_PSI = 10.0;

// PCA9685 / ULN2803 solenoid channels
const uint8_t SOLENOID_CHANNELS[] = {0, 1, 2, 3};
const uint8_t NUM_SOLENOIDS = sizeof(SOLENOID_CHANNELS) / sizeof(SOLENOID_CHANNELS[0]);

Adafruit_PWMServoDriver pwm = Adafruit_PWMServoDriver(0x40);

bool compressorRunning = false;
bool manualSolenoidState = false;
bool manualSolenoidState2 = false;
bool manualSolenoidState3 = false;
bool manualSolenoidState4 = false;

int highReadingCount = 0;
const int REQUIRED_CONSECUTIVE = 5;


float readPressurePSI() {
  uint32_t rawSum = 0;
  const int numSamples = 16;
  for (int i = 0; i < numSamples; i++) {
    rawSum += adc1_get_raw(PRESSURE_ADC_CHANNEL);
    delayMicroseconds(200);
  }
  int rawAvg = rawSum / numSamples;
  uint32_t gpioMilliVolts = esp_adc_cal_raw_to_voltage(rawAvg, &adcChars);
  float gpioVoltage = gpioMilliVolts / 1000.0;
  float actualVoltage = gpioVoltage / DIVIDER_RATIO;
  float psi = (actualVoltage - TRANSDUCER_MIN_V) * (MAX_PSI / (TRANSDUCER_MAX_V - TRANSDUCER_MIN_V));
  psi -= PSI_OFFSET;
  if (psi < 0) psi = 0;
  return psi;
}

void setSolenoid(uint8_t channel, bool on) {
  pwm.setPin(channel, on ? 4095 : 0, false);
}

void pulseSolenoid(uint8_t channel, uint8_t dutyPercent) {
  uint16_t pwmValue = map(dutyPercent, 0, 100, 0, 4095);
  pwm.setPWM(channel, 0, pwmValue);
}

void setCompressor(bool on) {
  digitalWrite(COMPRESSOR_MOSFET_PIN, on ? HIGH : LOW);
  compressorRunning = on;
}

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("compressor control starting...");

  pinMode(COMPRESSOR_MOSFET_PIN, OUTPUT);
  digitalWrite(COMPRESSOR_MOSFET_PIN, LOW);
  //buttons
  pinMode(MANUAL_BUTTON_PIN, INPUT_PULLUP);
  pinMode(MANUAL_BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(MANUAL_BUTTON_PIN_3, INPUT_PULLUP);
  pinMode(MANUAL_BUTTON_PIN_4, INPUT_PULLUP);

  adc1_config_width(ADC_WIDTH);
  adc1_config_channel_atten(PRESSURE_ADC_CHANNEL, ADC_ATTEN);
  
  esp_adc_cal_value_t calType = esp_adc_cal_characterize(ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH, 1100, &adcChars);
  switch (calType) {
    case ESP_ADC_CAL_VAL_EFUSE_TP:
      Serial.println("ADC calibration: Two Point");
      break;
    case ESP_ADC_CAL_VAL_EFUSE_VREF:
      Serial.println("ADC calibration: eFuse Vref");
      break;
    default:
      Serial.println("ADC calibration: Default Vref");
      break;
  }

  Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN);
  if (!pwm.begin()) {
    Serial.println("PCA9685 not detected");
    while (1) delay(1000);
  }
  pwm.setPWMFreq(1000);

  for (uint8_t i = 0; i < NUM_SOLENOIDS; i++) {
    setSolenoid(SOLENOID_CHANNELS[i], false);
  }

  Serial.println("Init success");
}

void loop() {
  float pressure = readPressurePSI();
  if (pressure >= PRESSURE_HIGH_PSI) {
    highReadingCount++;
} else {
    highReadingCount = 0;
}

//Turn on compressor if within activation threshold
if (!compressorRunning && pressure < PRESSURE_LOW_PSI) {
    setCompressor(true);
    Serial.println(">> Compressor ON");
} else if (compressorRunning && highReadingCount >= REQUIRED_CONSECUTIVE) {
    setCompressor(false);
    Serial.println(">> Compressor OFF");
    highReadingCount = 0;
}

  Serial.printf("Pressure: %.2f PSI | Compressor: %s\n",
                pressure, compressorRunning ? "ON" : "OFF");

  delay(200);
  bool reading  = digitalRead(MANUAL_BUTTON_PIN);
  bool reading2 = digitalRead(MANUAL_BUTTON_PIN_2);
  bool reading3 = digitalRead(MANUAL_BUTTON_PIN_3);
  bool reading4 = digitalRead(MANUAL_BUTTON_PIN_4);

  //debug button
  Serial.printf("BTN1: %s | BTN2: %s | BTN3: %s | BTN4: %s\n",
                reading  == LOW ? "PRESSED" : "released",
                reading2 == LOW ? "PRESSED" : "released",
                reading3 == LOW ? "PRESSED" : "released",
                reading4 == LOW ? "PRESSED" : "released");

bool buttonPressed = (reading == LOW);
if (buttonPressed != manualSolenoidState) {
  manualSolenoidState = buttonPressed;
  setSolenoid(MANUAL_SOLENOID_CHANNEL, manualSolenoidState);
  Serial.printf("Solenoid %d: %s\n", MANUAL_SOLENOID_CHANNEL,
                manualSolenoidState ? "OPEN" : "CLOSED");
}

bool buttonPressed2 = (reading2 == LOW);
if (buttonPressed2 != manualSolenoidState2) {
  manualSolenoidState2 = buttonPressed2;
  setSolenoid(MANUAL_SOLENOID_CHANNEL_2, manualSolenoidState2);
  Serial.printf("Solenoid %d: %s\n", MANUAL_SOLENOID_CHANNEL_2,
                manualSolenoidState2 ? "OPEN" : "CLOSED");
}

bool buttonPressed3 = (reading3 == LOW);
if (buttonPressed3 != manualSolenoidState3) {
  manualSolenoidState3 = buttonPressed3;
  setSolenoid(MANUAL_SOLENOID_CHANNEL_3, manualSolenoidState3);
  Serial.printf("Solenoid %d: %s\n", MANUAL_SOLENOID_CHANNEL_3,
                manualSolenoidState3 ? "OPEN" : "CLOSED");
}

bool buttonPressed4 = (reading4 == LOW);
if (buttonPressed4 != manualSolenoidState4) {
  manualSolenoidState4 = buttonPressed4;
  setSolenoid(MANUAL_SOLENOID_CHANNEL_4, manualSolenoidState4);
  Serial.printf("Solenoid %d: %s\n", MANUAL_SOLENOID_CHANNEL_4,
                manualSolenoidState4 ? "OPEN" : "CLOSED");
}
}
