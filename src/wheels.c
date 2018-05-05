#include "mr32.h"
#include "wheels.h"

speed_t wheel_speed;

void wheels_init() {
    wheel_speed.left = 0;
    wheel_speed.right = 0;
}

void wheels_update() {
    setVel2(wheel_speed.left, wheel_speed.right);
}
