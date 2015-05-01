/*
//Filename: pwmwithlib.c
//Description - This program demonstrates how to turn on
//		the pwm module on pin P8_13 and change period
//		and duty cycle with libBBB.
//
*/

#include "libBBB.h"
#include <dirent.h>
#include <time.h>

#define MGRNUM	9

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

int main(){
	int HELPER = helper(P8_19);
	initPWM(MGRNUM, P8_19);
	setPWMPeriod(HELPER, P8_19, 200000000);
	setPWMDuty(HELPER, P8_19, 0);
	setPWMOnOff(HELPER, P8_19, ON);
	HELPER = helper(P8_13);
	initPWM(MGRNUM, P8_13);
	setPWMPeriod(HELPER, P8_13, 200000000);
	setPWMDuty(HELPER, P8_13, 0);
	setPWMOnOff(HELPER, P8_13, ON);
	while(1);

	return 0;
}
