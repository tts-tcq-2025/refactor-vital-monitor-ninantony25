#pragma once

enum class VitalStatus 
{
  OK,
  TemperatureCritical,
  PulseRateOutOfRange,
  Spo2OutOfRange
};

VitalStatus checkVitals(float temperature, float pulseRate, float spo2);
void alert(VitalStatus status);
