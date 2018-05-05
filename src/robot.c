#include "robot.h"

#include "mr32.h"

void
robot_init()
{
  initPIC32();

  wheels_init();
  gps_init();
  obstacle_init();
  wheels_init();
}