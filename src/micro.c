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
  obstacle_init();

  wheel_speed.left = 50;
  wheel_speed.right = 50;
  wheels_update();
  int count = 0;
  int ticks = 0;

  int eye_state = 0;

  while (1) {
    if (ticks++ % 100000 == 0)
      count++;

    if (ticks % 10000)
      eye_rotate(eye_state++ % 2 == 0 ? -10 : 10);

    obstacle_update();
    if (obstacle_sensors.front < 200 || obstacle_sensors.left < 200 ||
        obstacle_sensors.right < 200) {

      move_stop();

      if (count % 2 == 0) {
        wheel_speed.left = +50;
        wheel_speed.right = -50;
      } else {
        wheel_speed.left = -50;
        wheel_speed.right = +50;
      }

      wheels_update();

      while (obstacle_sensors.right < 800 && obstacle_sensors.front < 400 &&
             obstacle_sensors.left < 800)
        obstacle_update();

      printf("obstacle cleared!\n");

      move_stop();

      wheel_speed.left = 50;
      wheel_speed.right = 50;
      wheels_update();
    }
  }
}
