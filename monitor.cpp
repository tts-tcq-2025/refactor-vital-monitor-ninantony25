#include "./monitor.h"
#include <iostream>
#include <thread>
#include <chrono>
#include <map>
#include <functional>

using std::cout, std::flush, std::this_thread::sleep_for, std::chrono::seconds;

VitalStatus checkVitals(float temperature, float pulseRate, float spo2) {
    if (temperature > 102 || temperature < 95)
        return VitalStatus::TemperatureCritical;
    if (pulseRate < 60 || pulseRate > 100)
        return VitalStatus::PulseRateOutOfRange;
    return (spo2 < 90) ? VitalStatus::OxygenSaturationOutOfRange : VitalStatus::OK;
}

void alertUser(
    VitalStatus status,
    std::function<void(const char*)> output,
    std::function<void()> sleep
)
   {
    static const std::map<VitalStatus, const char*> messages = {
        {VitalStatus::TemperatureCritical, "Temperature is critical!\n"},
        {VitalStatus::PulseRateOutOfRange, "Pulse Rate is out of range!\n"},
        {VitalStatus::OxygenSaturationOutOfRange, "Oxygen Saturation out of range!\n"}
    };

    auto it = messages.find(status);
    if (it == messages.end()) return;

    output(it->second);
    for (int i = 0; i < 6; ++i) {
        output("\r* ");
        sleep();
        output("\r *");
        sleep();
    }
}

int vitalsOk(float temperature, float pulseRate, float spo2) {
    VitalStatus status = checkVitals(temperature, pulseRate, spo2);
    if (status == VitalStatus::OK)
        return 1;
    alertUser(
        status,
        [](const char* msg) { cout << msg << flush; },
        []() { sleep_for(seconds(1)); }
    );
    return 0;
}
