#include <Wire.h>  
#include "MAX30100_PulseOximeter.h" 
#include "DecisionTree.h"

Eloquent::ML::Port::DecisionTree health_Classifier;

#define TEMPERATURE_SENSOR_PIN 32  // Analog pin for the temperature sensor (replace with the actual pin number)
#define HEART_RATE_SENSOR_PIN 35   // Analog pin for the heart rate sensor (replace with the actual pin number)

// Initialize the PulseOximeter library
PulseOximeter pox;

// Variable Declaration
float t;
int h;
int s;
int prediction;

void setup() {
  Serial.begin(9600);
  Serial.println("Welcome!");

  pinMode(TEMPERATURE_SENSOR_PIN, INPUT);  
  pinMode(HEART_RATE_SENSOR_PIN, INPUT);   

  // Initialize the Pulse Oximeter
  if (!pox.begin()) {
    Serial.println("Failed to initialize pulse oximeter!");
    while (1);
  } else {
    Serial.println("Pulse oximeter initialized successfully!");
  }
}

void loop() {
  delay(2000);

  // Sensor data Collection part

  // Read temperature value
  int temperatureValue = analogRead(TEMPERATURE_SENSOR_PIN);
  t = convertToCelsius(temperatureValue);
  Serial.print("Temperature (°C): ");
  Serial.println(t);

  // Read heart rate value
  h = analogRead(HEART_RATE_SENSOR_PIN);
  Serial.print("Heart Rate (bpm): ");
  Serial.println(h);

  // Read SpO2 value
  int s = pox.getSpO2();
  Serial.print("SpO2 (%): ");
  Serial.println(s);

  // Print values of heart_rate, temperature, and SpO2_saturation to serial monitor
  Serial.print(F("Heart_rate: "));
  Serial.print(h);
  Serial.print(F("  Temperature: "));
  Serial.print(t);
  Serial.print(F("  SpO2: "));
  Serial.println(s);

  float input[3] = {h, t, s};
  // Giving input values to predict Function
  int prediction = health_Classifier.predict(input);

  // Checking Condition
  Serial.print("Prediction: ");
  switch (prediction) {
    case 0:
      Serial.println("Normal");
      break;
    case 1:
      Serial.println("Serious");
      break;
    case 2:
      Serial.println("Dischargeable");
      break;
    default:
      Serial.println("Unknown");
      break;
  }

  Serial.println();
  delay(1000);
}

float convertToCelsius(int adcValue) {
  float voltage = adcValue * 3.3 / 4095.0;  // Convert ADC value to voltage for ESP32
  float temperatureCelsius = (voltage - 0.5) * 100;  // Convert voltage to temperature in Celsius
  return temperatureCelsius;
}
