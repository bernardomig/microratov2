#ifndef __GPS_H_
#define __GPS_H_

typedef struct
{
    double x;
    double y;
    double t;
} pose_t;

extern pose_t robot_pose;

void gps_init();

void gps_update();

#endif
