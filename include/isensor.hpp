#ifndef ISENSOR_HPP_
#define ISENSOR_HPP_

#include <sensorConfig.hpp>

class ISensor
{
public:
 const SensorConfig *config;  
    
public:
    virtual void loop() = 0;

};



#endif