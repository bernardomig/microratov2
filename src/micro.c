#include "mr32.h"

#include "eye.h"
#include "gps.h"
#include "obstacle.h"
#include "transportation.h"
#include "wheels.h"

pose_t poses[50];
int pose_c;

int
main()
{
  initPIC32();

  pose_c = 0;

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

  while (1) {
    if (ticks++ % 100000 == 0)
      count++;

    if (ticks % 10000)
      eye_rotate(eye_state++ % 2 == 0 ? -10 : 10);

    obstacle_update();
    if (obstacle_sensors.front < 200 || obstacle_sensors.left < 200 ||
        obstacle_sensors.right < 200) {

      move_stop();

      if ((obstacle_sensors.left < 200 || obstacle_sensors.right < 200) &&
          obstacle_sensors.front < 200) {

        gps_update();

        poses[pose_c++] = robot_pose;

        printf("poses: %d\n", pose_c);
      }

      if (obstacle_sensors.left < obstacle_sensors.right) {
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
