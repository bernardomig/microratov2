#include "mr32.h"

#include "obstacle.h"
#include "eye.h"
#include "wheels.h"
#include "gps.h"

int main()
{
    initPIC32();

    wheels_init();
    gps_init();

    int speed = 100;
    wheel_speed.left = speed;
    wheel_speed.right = speed;
    wheels_update();

    while (1)
    {
        printf("{ x=%f,\ty=%f,\tz=%f\t}\n", 
            robot_pose.x,
            robot_pose.y,
            robot_pose.t);
        
        gps_update();

        delay(2000);
    }
}
