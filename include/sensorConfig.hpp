#ifndef SENSOR_CONFIG_HPP_
#define SENSOR_CONFIG_HPP_

#include <stdint.h>

class SensorConfig {
public:
  enum sensor_t { SML_READER, ANALOG, DIGITAL };

public:
  const uint8_t pin;
  const char *name;
  const bool numeric_only;
  const bool status_led_enabled;
  const bool status_led_inverted;
  const uint8_t status_led_pin;
  const uint8_t interval;
  const sensor_t sensor_type;
};

#endif