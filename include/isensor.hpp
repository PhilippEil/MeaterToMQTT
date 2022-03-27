#ifndef ISENSOR_HPP_
#define ISENSOR_HPP_

#include <sensorConfig.hpp>

class ISensor {
public:
  const SensorConfig *config;
  void (*callback)(byte *buffer, size_t len, float value,
                   ISensor *sensor) = NULL;

public:
  virtual void loop() = 0;
};

#endif