#include "transportation.h"

#include "math.h"

#include "gps.h"
#include "robot.h"
#include "wheels.h"

pose_t goal;

const double K = 0.2;

inline double
distance2(pose_t p1, pose_t p2)
{
  const double x = p2.x - p1.x;
  const double y = p2.y - p1.y;
  return x * x + y * y;
}

inline double
projection(pose_t p1, pose_t p2)
{
  const double x = p2.x - p1.x;
  const double y = p2.y - p1.y;
  const double theta = robot_pose.t;
  const double C = cos(theta);
  const double S = sin(theta);
  return (x * C) + (y * S);
}

#include "mr32.h"

inline double
calculate_omega()
{
  return normalizeAngle(
    atan2((goal.y - robot_pose.y), (goal.x - robot_pose.x)) - robot_pose.t);
}

inline double
calculate_delta_theta()
{
  const double delta = normalizeAngle(goal.t - robot_pose.t);

  return delta;
}

inline double
calculate_delta_theta2()
{
  const double delta = calculate_delta_theta();

  return delta * delta;
}

inline double
calculate_delta_omega2()
{
  const double delta = calculate_omega();
  return delta * delta;
}

inline double
calculate_delta()
{
  pose_t current;
  current.x = robot_pose.x;
  current.y = robot_pose.y;
  return projection(current, goal);
}

inline double
calculate_distance()
{
  pose_t current;
  current.x = robot_pose.x;
  current.y = robot_pose.y;
  return distance2(current, goal);
}

inline pose_t
calculate_wheel_vel_rotation_to_goal()
{
  double t2 = 50 * calculate_omega();
  if (fabs(t2) > max_velocity)
    t2 = t2 / t2 * max_velocity;

  pose_t wheel_vel;
  wheel_vel.x = -t2;
  wheel_vel.y = +t2;

  return wheel_vel;
}

inline pose_t
calculate_wheel_vel_rotation_to_pose()
{
  double t2 = 50 * calculate_delta_theta();
  if (fabs(t2) > max_velocity)
    t2 = t2 / t2 * max_velocity;

  pose_t wheel_vel;
  wheel_vel.x = -t2;
  wheel_vel.y = +t2;

  return wheel_vel;
}

inline pose_t
calculate_wheel_vel_translation()
{
  pose_t wheel_vel;
  double t1 = 0.4 * calculate_delta();
  if (fabs(t1) > max_velocity)
    t1 = t1 / t1 * max_velocity;
  double t2 = 10 * calculate_omega();
  if (fabs(t2) > max_velocity)
    t2 = t2 / t2 * max_velocity;

  wheel_vel.x = (t1 - t2);
  wheel_vel.y = (t1 + t2);

  return wheel_vel;
}

void
move_init()
{
  goal.x = 0;
  goal.y = 0;
}

void
move_update_translation()
{
  gps_update();

  pose_t wheel_vel = calculate_wheel_vel_translation();

  wheel_speed.left = wheel_vel.x;
  wheel_speed.right = wheel_vel.y;

  wheels_update();
}

void
move_update_rotation_to_goal()
{
  gps_update();

  pose_t wheel_vel = calculate_wheel_vel_rotation_to_goal();

  wheel_speed.left = wheel_vel.x;
  wheel_speed.right = wheel_vel.y;

  wheels_update();
}

void
move_update_rotation_to_pose()
{
  gps_update();

  pose_t wheel_vel = calculate_wheel_vel_rotation_to_pose();

  wheel_speed.left = wheel_vel.x;
  wheel_speed.right = wheel_vel.y;

  wheels_update();
}

void
move_goto(pose_t point2goal)
{
  goal = point2goal;

  while (calculate_delta_omega2() < 0.2) {
    move_update_rotation_to_goal();
  }

  while (calculate_distance() > 400) {
    move_update_translation();
  }

  while (calculate_delta_theta2() < 0.2) {
    move_update_rotation_to_pose();
  }

  wheel_speed.left = 0;
  wheel_speed.right = 0;
  wheels_update();
}

#include <mr32.h>

void
move_rotate_to()
{

  while (calculate_delta_theta2() > 0.002) {

    int i;
    for (i = 0; i < 1000; i++)
      move_update_rotation_to_pose();

    printf("%f\n", calculate_delta_theta2());
  }

  wheel_speed.left = 0;
  wheel_speed.right = 0;
  wheels_update();
}

inline void
move_goto_to_point()
{
  printf("rotate to goal\n");

  if (calculate_distance() > 1000)
    while (calculate_delta_omega2() > 0.01) {

      int i;
      for (i = 0; i < 1000; i++)
        move_update_rotation_to_goal();

      printf("%f\n", calculate_delta_theta2());
    }

  while (calculate_distance() > 4000) {
    move_update_translation();
  }

  printf("translate\n");

  while (calculate_delta_theta2() > 0.01) {
    move_update_rotation_to_pose();
  }

  printf("rotate to pose\n");

  wheel_speed.left = 0;
  wheel_speed.right = 0;
  wheels_update();
}