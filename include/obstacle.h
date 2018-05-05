#ifndef __OBSTACLE_H__
#define __OBSTACLE_H__

typedef struct
{
  int left;
  int front;
  int right;
} obstacle_sensors_t;

extern obstacle_sensors_t obstacle_sensors;

void
obstacle_init();

void
obstacle_update();

#endif
