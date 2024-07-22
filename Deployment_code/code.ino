#include <Wire.h>
#include "MAX30100_PulseOximeter.h"
#include "DecisionTree.h"
#include <OneWire.h>
#include <DallasTemperature.h>

Eloquent::ML::Port::DecisionTree health_Classifier;

#define DS18B20 4

// Initialize the PulseOximeter library
PulseOximeter pox;
#define REPORTING_PERIOD_MS 1000
uint32_t tsLastReport = 0;

// Variable Declaration
float bodytemperature;
int BPM;
float SpO2;
int prediction;

// Callback (registered below) fired when a pulse is detected
void onBeatDetected() {
  Serial.println("Beat!");
}

// Define the struct for holding heart rate and SpO2 values
struct HeartRateData {
    float BPM;
    float SpO2;
};

// Declare the heart_rate function
HeartRateData heart_rate();

HeartRateData heart_rate() {
    pox.update();
    
    HeartRateData data;
    data.BPM = pox.getHeartRate();
    data.SpO2 = pox.getSpO2();

    return data;
}

OneWire oneWire(DS18B20);
DallasTemperature sensors(&oneWire);

void setup() {
  Serial.begin(115200);
  Serial.print("Initializing pulse oximeter..");
  if (!pox.begin()) {
    Serial.println("FAILED");
    for (;;);
  } 
  else {
    Serial.println("SUCCESS");
  }
  pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
  delay(500);
  pox.update();
  sensors.requestTemperatures();
  HeartRateData data = heart_rate();
  if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
    Serial.print("Heart rate: ");
    Serial.print(data.BPM);
    Serial.print(" bpm / SpO2: ");
    Serial.print(data.SpO2);
    Serial.println(" %");
  }
  bodytemperature = sensors.getTempCByIndex(0);
  Serial.print(bodytemperature);
  // Predict the health condition
  float input[3] = { data.BPM, (float)bodytemperature, data.SpO2 };
  prediction = health_Classifier.predict(input);

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
  tsLastReport = millis();
  Serial.println();
  delay(1000);
}
