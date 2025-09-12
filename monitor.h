#pragma once
#ifndef MONITOR_H
#define MONITOR_H

int spo2Ok(int spo2);
int tempOk(float temperature);
int pulseRateOk(int pulse);

// Declare combined vital check
int vitalsOk(float temperature, int pulseRate, int spo2);

#endif
