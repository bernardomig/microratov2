#ifndef __TRANSPORTATION_H__
#define __TRANSPORTATION_H__

#include "gps.h"

extern pose_t goal;

void
move_init();

void
move_update();

inline int
move_check();

inline void move_goto(pose_t);

inline void move_goto_to_point();

void move_rotate_to();

void move_debug();

#endif
