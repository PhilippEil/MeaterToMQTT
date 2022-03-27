#ifndef SENSOR_H
#define SENSOR_H

#include "debug.h"

#include <analog_sensor.hpp>
#include <digital_sensor.hpp>
#include <sensorConfig.hpp>
#include <sml_sensor.hpp>

using namespace std;

class Sensor {
private:
  ISensor *sensor;

public:
  const SensorConfig *config;

public:
  Sensor(const SensorConfig *config,
         void (*callback)(byte *buffer, size_t len, float value, ISensor *sensor)) {
    this->config = config;
    switch (this->config->sensor_type) {
    case SensorConfig::ANALOG:
      sensor = new Analog_sensor(config, callback);
      break;
    case SensorConfig::DIGITAL:
      sensor = new Digital_sensor(config, callback);
      break;
    case SensorConfig::SML_READER:
      sensor = new SML_Sensor(config, callback);
      break;
    }
  }

  void loop() { this->sensor->loop(); }
};

#endif