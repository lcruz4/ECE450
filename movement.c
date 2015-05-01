#include "libBBB.h"

void speed(int speed){
    int vel = 0;
    vel = ((float)speed*.01)*(int)200000000;
//Back Right Wheel
	setPWMPeriod(HELPER, P8_13, 200000000);
	setPWMDuty(HELPER, P8_13, vel);
	setPWMOnOff(HELPER, P8_13, ON);
//Front Right Wheel
	setPWMPeriod(HELPER, P9_14, 200000000);
	setPWMDuty(HELPER, P9_14, vel);
	setPWMOnOff(HELPER, P9_14, ON);
//Back Left Wheel
	setPWMPeriod(HELPER, P8_19, 200000000);
	setPWMDuty(HELPER, P8_19, vel);
	setPWMOnOff(HELPER, P8_19, ON);
//Front Left Wheel
	setPWMPeriod(HELPER, P9_16, 200000000);
	setPWMDuty(HELPER, P9_16, vel);
	setPWMOnOff(HELPER, P9_16, ON);
}

void turn_right(){
    setPinValue(45, 1);		//left wheels
    setPinValue(60, 0);		//right wheels
}

void forward(){
    setPinValue(45, 1);		//left wheels
    setPinValue(60, 1);		//right wheels
}