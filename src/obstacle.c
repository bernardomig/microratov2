#include "obstacle.h"

#include "mr32.h"

obstacle_sensors_t obstacle_sensors;

// Constants for the calculation of the range finders
// a = 1024 / 3.3V * 28
const float a = 8688.4;
const float b = 0.42;

inline int convert_to_mm(int reading) {
    return (int)(a / reading - b);
}

void init_obstacle_sensors() {
    enableObstSens();
    obstacle_sensors.left = 0;
    obstacle_sensors.front = 0;
    obstacle_sensors.right = 0;
}

void update_obstacle_sensors() {

    readAnalogSensors();

    obstacle_sensors.left
        = convert_to_mm(analogSensors.obstSensLeft);
    obstacle_sensors.right
        = convert_to_mm(analogSensors.obstSensRight);
    obstacle_sensors.front
        = convert_to_mm(analogSensors.obstSensFront);

}