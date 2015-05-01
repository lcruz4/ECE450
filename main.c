#include "libBBB.h"

#define MGRNUM  9
#define HELPER  15

int main()
{
        initPWM( MGRNUM, P8_13 );
        initPWM( MGRNUM, P9_14 );
        initPWM( MGRNUM, P8_18 );
        initPWM( MGRNUM, P9_16 );
        while(1){
                forward();
                speed(5, HELPER);
        }

        return 0;
}
