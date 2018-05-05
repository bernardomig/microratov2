#include "mr32.h"

#include "eye.h"

int current_angle;

void
init_eye()
{
  current_angle = 0;
  setServoPos(0);
}

inline int
eye_read()
{
  return readBeaconSens();
}

void
eye_rotate(int angle)
{
  current_angle = angle;
  setServoPos(angle);
}

inline int
eye_angle()
{
  return current_angle;
}
