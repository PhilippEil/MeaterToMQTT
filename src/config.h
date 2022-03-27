#ifndef CONFIG_H
#define CONFIG_H

#include "Arduino.h"
#include "Sensor.h"

const char *VERSION = "0.0.4";

// Modifying the config version will probably cause a loss of the existig
// configuration. Be careful!
const char *CONFIG_VERSION = "0.0.1";

const char *WIFI_AP_SSID = "SMLReader";
const char *WIFI_AP_DEFAULT_PASSWORD = "";

static const SensorConfig SENSOR_CONFIGS[] = {
    {.pin = D2,
     .name = "1",
     .numeric_only = false,
     .status_led_enabled = true,
     .status_led_inverted = true,
     .status_led_pin = LED_BUILTIN,
     .interval = 0,
     .sensor_type = SensorConfig::SML_READER,
     .factor = 1}
     ,
    {.pin = D3,
     .name = "GasSensorDigital_m3",
     .numeric_only = false,
     .status_led_enabled = true,
     .status_led_inverted = true,
     .status_led_pin = LED_BUILTIN,
     .interval = 30,
     .sensor_type = SensorConfig::DIGITAL,
     .factor = 0.01}
    // ,
    // {.pin = A0,
    //  .name = "GasSensorAnalog_m3",
    //  .numeric_only = false,
    //  .status_led_enabled = true,
    //  .status_led_inverted = true,
    //  .status_led_pin = LED_BUILTIN,
    //  .interval = 30,
    //  .sensor_type = SensorConfig::ANALOG,
    //  .factor = 0.01}
     };

const uint8_t NUM_OF_SENSORS = sizeof(SENSOR_CONFIGS) / sizeof(SensorConfig);

#endif