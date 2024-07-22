#include <Wire.h>
#include "MAX30100_PulseOximeter.h"

#define REPORTING_PERIOD_MS 1000

PulseOximeter pox;
uint32_t tsLastReport = 0;

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

void setup() {
    Serial.begin(115200);
    Serial.print("Initializing pulse oximeter..");

    if (!pox.begin()) {
        Serial.println("FAILED");
        for (;;);
    } else {
        Serial.println("SUCCESS");
    }
    
    pox.setOnBeatDetectedCallback(onBeatDetected);
}

void loop() {
    HeartRateData data = heart_rate();

    if (millis() - tsLastReport > REPORTING_PERIOD_MS) {
        Serial.print("Heart rate: ");
        Serial.print(data.BPM);
        Serial.print(" bpm / SpO2: ");
        Serial.print(data.SpO2);
        Serial.println(" %");
        tsLastReport = millis();
    }
}

HeartRateData heart_rate() {
    pox.update();
    
    HeartRateData data;
    data.BPM = pox.getHeartRate();
    data.SpO2 = pox.getSpO2();

    return data;
}
