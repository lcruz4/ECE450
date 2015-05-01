/*Copyright (C) 2013 Gavin Strunk

Permission is hereby granted, free of charge, to any person obtaining a copy of this software $

The above copyright notice and this permission notice shall be included in all copies or subst$

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING $
*/


#ifndef _libBBB_H_
#define _libBBB_H_

//Includes
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <termios.h>
#include <fcntl.h>
#include <unistd.h>
#include <linux/i2c-dev.h>
#include <sys/ioctl.h>

//Type definitions
typedef struct {
      struct termios u;
}UART;

//Definitions
#define OUT     "out"
#define IN      "in"
#define ON      1
#define OFF     0

#define USR1    "usr1"
#define USR2    "usr2"
#define USR3    "usr3"
#define P8_13   "P8_13"     //RR
#define P8_18   "P8_18"     //LR
#define P9_14   "P9_14"     //RF
#define P9_16   "P9_16"     //LF
#define P9_12   "P9_12"     //Rdir
#define P8_11   "P8_11"     //Ldir
#define E       65
#define RS      27
#define D4      46
#define D5      47
#define D6      26
#define D7      44
#define AIN0    "/AIN0"
#define AIN1    "/AIN1"
#define AIN2    "/AIN2"
#define AIN3    "/AIN3"
#define AIN4    "/AIN4"
#define AIN5    "/AIN5"
#define AIN6    "/AIN6"
#define AIN7    "/AIN7"

//Device Tree Overlay
int addOverlay(char *dtb, char *overname);

//USR Prototypes
int setUsrLedValue(char* led, int value);

//GPIO Prototypes
int initPin(int pinnum);
int setPinDirection(int pinnum, char* dir);
int setPinValue(int pinnum, int value);
int getPinValue(int pinnum);

//PWM Prototypes
int initPWM(int mgrnum, char* pin);
int setPWMPeriod(int helpnum, char* pin, int period);
int setPWMDuty(int helpnum, char* pin, int duty);
int setPWMOnOff(int helpnum, char* pin, int run);

//SPI Prototypes
int initSPI(int modnum);
void closeSPI(int device);
int writeByteSPI(int device,unsigned char *data);
int writeBufferSPI(int device, unsigned char *buf, int len);
int readByteSPI(int device, unsigned char *data);
int readBufferSPI(int device, int numbytes, unsigned char *buf);

//ADC Prototypes
int initADC(int mgrnum);
int readADC(int helpnum, char* ach);

//Time Prototypes
void pauseSec(int sec);
int  pauseNanoSec(long nano);

//Movement Prototypes
void speed(int speed,int HELPER);
void turn_right();
void forward();
#endif
