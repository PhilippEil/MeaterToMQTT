#ifndef ANALOG_SENSOR_HPP_
#define ANALOG_SENSOR_HPP_

#include "debug.h"
#include <isensor.hpp>

class Analog_sensor : public ISensor {
private:
  static constexpr int FILTER_SIZE = 500;
  static constexpr int TRIGGER_DISTANZ = 10;
  static constexpr int UPDATE_RATE_MS = 10;

private:
  bool m_init{false};
  uint32_t lastUpdate;
  uint32_t lastRead;
  uint32_t clickCount{0};
  float sum{0};
  int readings[FILTER_SIZE]{0};
  int readIndex;
  int average;
  int analogValue;
  int upperLimit;
  int lowerLimit;
  bool lock{false};

public:
  Analog_sensor(const SensorConfig *config,
                void (*callback)(byte *buffer, size_t len, float value,
                                 ISensor *sensor));
  ~Analog_sensor();

  void loop();
};

Analog_sensor::Analog_sensor(const SensorConfig *config,
                             void (*callback)(byte *buffer, size_t len,
                                              float value, ISensor *sensor)) {
  this->config = config;
  DEBUG("Initializing sensor %s", this->config->name);
  this->callback = callback;

  this->analogValue = analogRead(this->config->pin);
  for (int i = 0; i < FILTER_SIZE; i++) {
    this->readings[readIndex] = this->analogValue;
  }
}

Analog_sensor::~Analog_sensor() {}

void Analog_sensor::loop() {
  if ((millis() - this->lastRead) >= this->UPDATE_RATE_MS) {
    this->lastRead = millis();
    this->analogValue = analogRead(this->config->pin);
    this->sum = this->sum - this->readings[readIndex];
    this->readings[readIndex] = this->analogValue;
    this->sum = this->sum + readings[readIndex];
    this->readIndex++;

    if (this->readIndex >= FILTER_SIZE) {
      this->readIndex = 0;
    }

    this->average = this->sum / FILTER_SIZE;
    this->upperLimit = this->average + TRIGGER_DISTANZ;
    this->lowerLimit = this->average - TRIGGER_DISTANZ;

    //DEBUG("sensor %s; analogValue:%d, average:%d, upperLimit:%d, lowerLimit:%d",this->config->name ,lastRead, average, upperLimit, lowerLimit);
    DEBUG("sensor %s; analogValue:%d, average:%d, lowerLimit:%d, upperLimit:%d ,counter:%d",this->config->name ,analogValue, average, lowerLimit,upperLimit,clickCount);

    if (this->analogValue < this->lowerLimit && this->lock == false) {
      this->clickCount++;
      this->lock = true;
      DEBUG("increment count from sensor %s to %d", this->config->name,
            this->clickCount);
    }
    if (analogValue > this->average) {
      this->lock = false;
    }
  }

  if ((millis() - this->lastUpdate) >= (this->config->interval * 1000)) {
    this->lastUpdate = millis();
    float transmitValue = (float)this->clickCount * this->config->factor;
    this->callback(NULL, 0, transmitValue, this);
    this->clickCount = 0;
    DEBUG("clear count from sensor %s", this->config->name);
  }
  yield();
}

#endif