#include <gtest/gtest.h>
#include "./monitor.h"

TEST(Monitor, NotOkWhenAnyVitalIsOffRange) {
    ASSERT_FALSE(vitalsOk(99, 102, 70)); // Pulse high, SpO2 low
    ASSERT_FALSE(vitalsOk(103, 70, 98)); // Temp high
    ASSERT_FALSE(vitalsOk(94, 70, 98));  // Temp low
    ASSERT_FALSE(vitalsOk(98, 59, 98));  // Pulse low
    ASSERT_FALSE(vitalsOk(98, 101, 98)); // Pulse high
    ASSERT_FALSE(vitalsOk(98, 70, 89));  // SpO2 low
}

TEST(Monitor, OkWhenAllVitalsInRange) {
    ASSERT_TRUE(vitalsOk(98.1, 70, 98));
    ASSERT_TRUE(vitalsOk(95, 60, 90));
    ASSERT_TRUE(vitalsOk(102, 100, 90));
}

TEST(Monitor, CheckVitalsReturnsCorrectStatus) {
    EXPECT_EQ(checkVitals(103, 70, 98), VitalStatus::TemperatureCritical);
    EXPECT_EQ(checkVitals(94, 70, 98), VitalStatus::TemperatureCritical);
    EXPECT_EQ(checkVitals(98, 59, 98), VitalStatus::PulseRateOutOfRange);
    EXPECT_EQ(checkVitals(98, 101, 98), VitalStatus::PulseRateOutOfRange);
    EXPECT_EQ(checkVitals(98, 70, 89), VitalStatus::OxygenSaturationOutOfRange);
    EXPECT_EQ(checkVitals(98.1, 70, 98), VitalStatus::OK);
}
