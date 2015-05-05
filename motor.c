/*
//Filename: pwmwithlib.c
//Description - This program demonstrates how to turn on
//		the pwm module on pin P8_13 and change period
//		and duty cycle with libBBB.
//
*/

#include "motor.h"

int LEFT_HELPER = 0;
int RIGHT_HELPER = 0;

int helper(char *pin){
  int i = 0;
  char str[50] = "/sys/devices/ocp.3/pwm_test_";
  char stri[3];
  char str2[50] = "";
  DIR *dir;

  strcat(str,pin);
  strcat(str,".");
  sprintf(stri, "%d", i++);
  strcpy(str2,str);
  strcat(str2,stri);
  while((dir = opendir(str2))==NULL){
    sprintf(stri, "%d", i++);
    strcpy(str2,str);
    strcat(str2,stri);
  }
  closedir(dir);
  return --i;
}

void initMotor(){
	initPin(P8_11);
	initPin(P9_12);
	setPinDirection(P8_11, OUT);
	setPinValue(P8_11,1);
	setPinDirection(P9_12, OUT);
	setPinValue(P9_12,1);

	initPWM(MGRNUM, P8_13);
	initPWM(MGRNUM, P9_14);
	LEFT_HELPER = helper(P8_13);
	RIGHT_HELPER = helper(P9_14);
	setPWMPeriod(LEFT_HELPER, P8_13, 500000);
	setPWMPeriod(RIGHT_HELPER, P9_14, 500000);
	stop();
	setPWMOnOff(LEFT_HELPER, P8_13, ON);
	setPWMOnOff(RIGHT_HELPER, P9_14, ON);
}

void forward(int duty){
	setPinValue(P8_11,1);	//left wheels forward
	setPinValue(P9_12,1);	//right wheels forward
	speed(duty);
}

void backward(int duty){
	setPinValue(P8_11,0);	//left wheels backward
	setPinValue(P9_12,0);	//right wheels backward
	speed(duty);
}

void arc_left(int duty){
	setPinValue(P9_12,1);	//right wheels forward
	speed(duty);
	setPWMDuty(LEFT_HELPER, P8_13, 0);
}

void arc_right(int duty){
	setPinValue(P8_11,1);	//left wheels forward
	speed(duty);
	setPWMDuty(RIGHT_HELPER, P9_14, 0);
}

void spin_left(int duty){
	setPinValue(P8_11,0);	//left wheels backward
	setPinValue(P9_12,1);	//right wheels forward
	speed(duty);
}

void spin_right(int duty){
	printf("DEBUG\n");
	printf("ret1:%d\n",setPinValue(P8_11,1));	//left wheels forward
	printf("ret2:%d\n",setPinValue(P9_12,0));	//right wheels backward
	speed(duty);
}

void speed(int duty){
	setPWMDuty(LEFT_HELPER, P8_13,  duty*5000);
	setPWMDuty(RIGHT_HELPER, P9_14, duty*5000);
}

void stop(){
	setPWMDuty(LEFT_HELPER, P8_13, 500000);
	setPWMDuty(RIGHT_HELPER, P9_14, 500000);
}
