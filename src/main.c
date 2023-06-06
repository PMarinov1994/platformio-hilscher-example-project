#include "blinky_demo.h"

int main()
{

#ifdef RUN_BLINKY
    return blinky_demo();
#else
    while (1)
    {
    };
#endif
}
