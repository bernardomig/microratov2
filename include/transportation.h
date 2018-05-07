#ifndef __TRANSPORTATION_H__
#define __TRANSPORTATION_H__

const double maximum_delta;

typedef struct {
    double x;
    double y;
} point_t;

extern point_t goal;

void move_init();

void move_update();

inline int move_check();

void move_debug();

#endif
