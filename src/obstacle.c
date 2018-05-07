#include "obstacle.h"

#include "mr32.h"

obstacle_sensors_t obstacle_sensors;

// Constants for the calculation of the range finders
// a = 1024 / 3.3V * 28
const double a = 8688.4;
const double b = 0.42;

inline double
convert_to_mm(int reading)
{
  return (a / reading - b);
}

void
obstacle_init()
{
  enableObstSens();
  obstacle_sensors.left = 0;
  obstacle_sensors.front = 0;
  obstacle_sensors.right = 0;
}

void
obstacle_update()
{

  readAnalogSensors();

  obstacle_sensors.left = convert_to_mm(analogSensors.obstSensLeft);
  obstacle_sensors.right = convert_to_mm(analogSensors.obstSensRight);
  obstacle_sensors.front = convert_to_mm(analogSensors.obstSensFront);
}
