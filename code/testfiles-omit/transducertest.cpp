//Transducer test (SUCCEEDED, needs calibration)

#include <Arduino.h>
#include "driver/adc.h"
#include "esp_adc_cal.h"

// GPIO34 = ADC1_CHANNEL_6 on ESP32
#define ADC_CHANNEL ADC1_CHANNEL_6
#define ADC_ATTEN   ADC_ATTEN_DB_11   // full ~0-3.3V range
#define ADC_WIDTH   ADC_WIDTH_BIT_12  // 0-4095

// Voltage divider: R1=10k->signal, R2=20k->GND
const float DIVIDER_RATIO = 20000.0 / (10000.0 + 20000.0);  // 0.667

// Transducer spec
const float TRANSDUCER_MIN_V = 0.5;
const float TRANSDUCER_MAX_V = 4.5;
const float MAX_PSI = 150.0;

esp_adc_cal_characteristics_t adcChars;

void setup() {
  Serial.begin(115200);
  delay(500);
  Serial.println("Pressure transducer checker (calibrated ADC) starting...");

  adc1_config_width(ADC_WIDTH);
  adc1_config_channel_atten(ADC_CHANNEL, ADC_ATTEN);

  esp_adc_cal_value_t calType = esp_adc_cal_characterize(
    ADC_UNIT_1, ADC_ATTEN, ADC_WIDTH, 1100, &adcChars
  );

  switch (calType) {
    case ESP_ADC_CAL_VAL_EFUSE_TP:
      Serial.println("ADC calibration: Two Point (best accuracy)");
      break;
    case ESP_ADC_CAL_VAL_EFUSE_VREF:
      Serial.println("ADC calibration: eFuse Vref");
      break;
    default:
      Serial.println("ADC calibration: Default Vref (least accurate, no eFuse data)");
      break;
  }
}

void loop() {
  //adc noise smoothing
  uint32_t rawSum = 0;
  const int numSamples = 16; //arbitrary
  for (int i = 0; i < numSamples; i++) {
    rawSum += adc1_get_raw(ADC_CHANNEL);
    delayMicroseconds(200);
  }
  int rawAvg = rawSum / numSamples;

  uint32_t gpioMilliVolts = esp_adc_cal_raw_to_voltage(rawAvg, &adcChars);
  float gpioVoltage = gpioMilliVolts / 1000.0;

  float actualVoltage = gpioVoltage / DIVIDER_RATIO;
  float psi = (actualVoltage - TRANSDUCER_MIN_V) * (MAX_PSI / (TRANSDUCER_MAX_V - TRANSDUCER_MIN_V));
  if (psi < 0) psi = 0;

  Serial.printf(
    "Raw: %4d | GPIO34 V: %.3f | Transducer V: %.3f | PSI: %.2f\n",
    rawAvg, gpioVoltage, actualVoltage, psi
  );

  delay(300);
}
