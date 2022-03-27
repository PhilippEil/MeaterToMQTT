#ifndef ANALOG_SENSOR_HPP_
#define ANALOG_SENSOR_HPP_

#include <isensor.hpp>

class Analog_sensor: public ISensor
{
private:
    /* data */
public:
    Analog_sensor(const SensorConfig *config,
         void (*callback)(byte *buffer, size_t len, ISensor *sensor));
    ~Analog_sensor();

    void loop();
};

Analog_sensor::Analog_sensor(const SensorConfig *config,
         void (*callback)(byte *buffer, size_t len, ISensor *sensor))
{
}

Analog_sensor::~Analog_sensor()
{
}

void Analog_sensor::loop(){

}



#endif