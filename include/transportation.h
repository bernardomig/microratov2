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

void
move_rotate_to();

inline int move_goto_to_point();

inline void move_stop();

void move_debug();

#endif
