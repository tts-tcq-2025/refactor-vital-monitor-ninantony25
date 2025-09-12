
#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, TemperatureOutOfRange) {
  EXPECT_EQ(checkVitals(103, 80, 95), VitalStatus::TemperatureCritical);
  EXPECT_EQ(checkVitals(94, 80, 95), VitalStatus::TemperatureCritical);
}

TEST(Monitor, PulseRateOutOfRange) {
  EXPECT_EQ(checkVitals(98.6, 55, 95), VitalStatus::PulseRateOutOfRange);
  EXPECT_EQ(checkVitals(98.6, 105, 95), VitalStatus::PulseRateOutOfRange);
}

TEST(Monitor, Spo2OutOfRange) {
  EXPECT_EQ(checkVitals(98.6, 80, 85), VitalStatus::Spo2OutOfRange);
}

TEST(Monitor, AllVitalsNormal) {
  EXPECT_EQ(checkVitals(98.6, 80, 95), VitalStatus::OK);
}
