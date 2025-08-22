/*#include "./monitor.h"
#include <assert.h>
#include <thread>
#include <chrono>
#include <iostream>
using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

int vitalsOk(float temperature, float pulseRate, float spo2){
  if (temperature > 102 || temperature < 95) {
    cout << "Temperature is critical!\n";
    for (int i = 0; i < 6; i++) {
      cout << "\r* " << flush;
      sleep_for(seconds(1));
      cout << "\r *" << flush;
      sleep_for(seconds(1));
    }
    return 0;
  } else if (pulseRate < 60 || pulseRate > 100) {
    cout << "Pulse Rate is out of range!\n";
    for (int i = 0; i < 6; i++) {
      cout << "\r* " << flush;
      sleep_for(seconds(1));
      cout << "\r *" << flush;
      sleep_for(seconds(1));
    }
    return 0;
  } else if (spo2 < 90) {
    cout << "Oxygen Saturation out of range!\n";
    for (int i = 0; i < 6; i++) {
      cout << "\r* " << flush;
      sleep_for(seconds(1));
      cout << "\r *" << flush;
      sleep_for(seconds(1));
    }
    return 0;
  }
  return 1;
}*/

#include <iostream>
#include <thread>
#include <chrono>
enum class VitalStatus 
{
    OK,
    TemperatureCritical,
    PulseRateOutOfRange,
    OxygenSaturationOutOfRange
};

VitalStatus checkVitals(float temperature, float pulseRate, float spo2);

void alertUser(
    VitalStatus status,
    void(*output)(const char*),
    void(*sleep)()
);

VitalStatus checkVitals(float temperature, float pulseRate, float spo2)
{
    if (temperature > 102 || temperature < 95)
        return VitalStatus::TemperatureCritical;
    if (pulseRate < 60 || pulseRate > 100)
        return VitalStatus::PulseRateOutOfRange;
    return (spo2 < 90) ? VitalStatus::OxygenSaturationOutOfRange : VitalStatus::OK;
}

void alertUser(
    VitalStatus status,
    void(*output)(const char*),
    void(*sleep)()
) 
{
    const char* message = nullptr;
    switch (status) {
        case VitalStatus::TemperatureCritical:
            message = "Temperature is critical!\n";
            break;
        case VitalStatus::PulseRateOutOfRange:
            message = "Pulse Rate is out of range!\n";
            break;
        case VitalStatus::OxygenSaturationOutOfRange:
            message = "Oxygen Saturation out of range!\n";
            break;
        default:
            return;
    }
    output(message);
    for (int i = 0; i < 6; ++i) 
    {
        output("\r* ");
        sleep();
        output("\r *");
        sleep();
    }
}

// --- Output and sleep functions ---

void consoleOutput(const char* msg) 
{
    std::cout << msg << std::flush;
}

void oneSecondSleep() 
{
    std::this_thread::sleep_for(std::chrono::seconds(1));
}

int main() 
{
    float temperature = 103, pulseRate = 80, spo2 = 95;
    VitalStatus status = checkVitals(temperature, pulseRate, spo2);
    if (status != VitalStatus::OK) 
    {
        alertUser(status, consoleOutput, oneSecondSleep);
        return 0;
    }
    std::cout << "Vitals are OK\n";
    return 1;
}
