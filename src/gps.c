#include "mr32.h"

#include "gps.h"

pose_t robot_pose;

void
gps_init()
{
  robot_pose.x = 0;
  robot_pose.y = 0;
  robot_pose.t = 0;
}

void
gps_update()
{
  getRobotPos(&robot_pose.x, &robot_pose.y, &robot_pose.t);
}
