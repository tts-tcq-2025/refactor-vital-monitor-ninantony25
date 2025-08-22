#pragma once

enum class VitalStatus {
    OK,
    TemperatureCritical,
    PulseRateOutOfRange,
    OxygenSaturationOutOfRange
};

VitalStatus checkVitals(float temperature, float pulseRate, float spo2);

int vitalsOk(float temperature, float pulseRate, float spo2);
