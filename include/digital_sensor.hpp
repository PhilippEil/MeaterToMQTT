#ifndef DIGITAL_SENSOR_HPP_
#define DIGITAL_SENSOR_HPP_

#include <isensor.hpp>
#include <stdint.h>

class Digital_sensor: public ISensor
{
private:
    /* data */
public:
    Digital_sensor(const SensorConfig *config,
         void (*callback)(byte *buffer, size_t len, ISensor *sensor));
    ~Digital_sensor();

    void loop(void);
};

Digital_sensor::Digital_sensor(const SensorConfig *config,
         void (*callback)(byte *buffer, size_t len, ISensor *sensor))
{
}

Digital_sensor::~Digital_sensor()
{
}

void Digital_sensor::loop(){

}

#endif