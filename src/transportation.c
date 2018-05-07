#include "transportation.h"

#include "math.h"

#include "gps.h"
#include "robot.h"
#include "wheels.h"

point_t goal;

const double K = 0.2;

inline double
distance(point_t p1, point_t p2)
{
  const double x = p2.x - p1.x;
  const double y = p2.y - p1.y;
  const double theta = robot_pose.t;
  const double C = cos(theta);
  const double S = sin(theta);
  return (x * C) - (y * S);
}

inline double
calculate_omega()
{
  return atan2((goal.y - robot_pose.y), (goal.x - robot_pose.x)) - robot_pose.t;
}

inline double
calculate_delta()
{
  point_t current;
  current.x = robot_pose.x;
  current.y = robot_pose.y;
  return distance(current, goal);
}

inline point_t
calculate_wheel_vel()
{
  point_t wheel_vel;
  double t1 = 1 * calculate_delta();
  if (fabs(t1) > max_velocity)
    t1 = t1 / t1 * max_velocity;
  double t2 = 0.0 * calculate_omega();
  if (fabs(t2) > max_velocity)
    t2 = t2 / t2 * max_velocity;
  wheel_vel.x = t1 - t2;
  wheel_vel.y = t1 + t2;

  return wheel_vel;
}

void
move_init()
{
  goal.x = 0;
  goal.y = 0;
}

#include "mr32.h"

void
move_debug()
{
  printf("angle = %f\n", calculate_omega());
  printf("distance = %f\n", calculate_delta());
  point_t vel = calculate_wheel_vel();
  printf("vel_x = %f\n", vel.x);
  printf("vel_y = %f\n", vel.y);
}

void
move_update()
{
  gps_update();

  point_t wheel_vel = calculate_wheel_vel();

  wheel_speed.left = wheel_vel.x;
  wheel_speed.right = wheel_vel.y;

  wheels_update();
}
