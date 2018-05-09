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

  while (!startButton())
    ;

  wheel_speed.left = 50;
  wheel_speed.right = 50;
  wheels_update();
  int count = 0;
  int ticks = 0;

  int eye_state = 0;

  int reached = 0;

  while (1) {

    leds(0);

    if (ticks++ % 100000 == 0)
      count++;

    if (ticks % 10000)
      eye_rotate(eye_state++ % 2 == 0 ? -10 : 10);

    if (readLineSensors(0) && reached == 0) {

      wheel_speed.left = 0;
      wheel_speed.right = 0;
      wheels_update();

      leds(0b1111);

      wait(3);

      wheel_speed.left = 50;
      wheel_speed.right = -50;
      wheels_update();

      while (readLineSensors(0))
        ;

      wheel_speed.left = 50;
      wheel_speed.right = 50;
      wheels_update();

      reached = 1;
    }


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

      move_stop();

      wheel_speed.left = 50;
      wheel_speed.right = 50;
      wheels_update();
    }
  }
}
