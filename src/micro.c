#include "mr32.h"

#include "eye.h"
#include "gps.h"
#include "obstacle.h"
#include "transportation.h"
#include "wheels.h"

int
main()
{
  initPIC32();

  wheels_init();
  gps_init();
  move_init();

  goal.x = 100;
  goal.y = 0;

  while (1) {

    printf("robot_position = {%f,\t%f\t,%f\t}\n",
           robot_pose.x,
           robot_pose.y,
           robot_pose.t);
    move_debug();

    int i;
    for (i = 0; i < 100; ++i)
      move_update();
  }
}
