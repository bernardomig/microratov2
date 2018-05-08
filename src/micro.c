#include "mr32.h"

#include "eye.h"
#include "gps.h"
#include "obstacle.h"
#include "transportation.h"
#include "wheels.h"

int
main()
{
  initPIC32();

  wheels_init();
  gps_init();
  move_init();

  pose_t to_go[4];
  to_go[0].x = 0;
  to_go[0].y = 0;
  to_go[0].t = 0;

  to_go[1].x = 500;
  to_go[1].y = 0;
  to_go[1].t = PI / 2;

  to_go[2].x = 500;
  to_go[2].y = 500;
  to_go[2].t = PI;

  to_go[3].x = 0;
  to_go[3].y = 500;
  to_go[3].t = 3 * PI / 2;


  while (1) {
    int i;
    for (i = 0; i < 4; ++i) {
      goal = to_go[i];
      move_goto_to_point();
    }
  }

  while (1)
    ;
  ;
}
