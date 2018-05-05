#include "mr32.h"

int main()
{
    initPIC32();
	closedLoopControl( FALSE );

    while(1) {
        readAnalogSensors();

        
        delay(1000);
    }
}
