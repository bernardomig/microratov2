#ifndef __WHEELS_H__
#define __WHEELS_H__

typedef struct
{
  double left;
  double right;
} speed_t;

extern speed_t wheel_speed;

void
wheels_init();

void
wheels_update();

#endif
