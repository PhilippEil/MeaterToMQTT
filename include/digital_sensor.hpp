#ifndef DIGITAL_SENSOR_HPP_
#define DIGITAL_SENSOR_HPP_

#include "debug.h"
#include <Arduino.h>
#include <isensor.hpp>

class Digital_sensor : public ISensor {
private:
  uint32_t lastUpdate;
  uint32_t clickCount{0};
  bool lastState{false};

public:
  Digital_sensor(const SensorConfig *config,
                 void (*callback)(byte *buffer, size_t len, float value,
                                  ISensor *sensor));
  ~Digital_sensor();

  void loop(void);
};

Digital_sensor::Digital_sensor(const SensorConfig *config,
                               void (*callback)(byte *buffer, size_t len,
                                                float value, ISensor *sensor)) {
  this->config = config;
  DEBUG("Initializing sensor %s...", this->config->name);
  this->callback = callback;
  this->callback(NULL, 0, 0, this);
  this->lastUpdate = millis();
}

Digital_sensor::~Digital_sensor() {}

void Digital_sensor::loop() {
  bool currentState = digitalRead(this->config->pin);
  if (currentState != lastState && currentState == true) {
    clickCount++;
    DEBUG("increment count from sensor %s to %d", this->config->name, this->clickCount);
  }
  lastState = currentState;

  if ((millis() - this->lastUpdate) >= (this->config->interval * 1000)) {
    this->lastUpdate = millis();
    float transmitValue = (float)this->clickCount * this->config->factor;
    this->callback(NULL, 0, transmitValue , this);
    clickCount = 0;
    DEBUG("clear count from sensor %s...", this->config->name);
  }
  yield();
}

#endif