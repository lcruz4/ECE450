/*
//Filename: libBBB.h
//
//Description - This is the main header file for
//		the libBBB library.
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
#define OUT	"out"
#define IN	"in"
#define ON	1
#define OFF	0

#define USR1	"usr1"
#define USR2	"usr2"
#define USR3	"usr3"
#define P8_13	"P8_13"		//Rear right wheel
#define P9_14	"P9_14"		//Front right wheel
#define P9_12	60		//Direction Right
#define P8_11	45		//Direction Left
#define P8_8    67		//Left Wheel encoder

#define E	65
#define RS	27
#define D4	46
#define D5	47
#define D6	26
#define D7	44
#define AIN0	"/AIN0"
#define AIN1	"/AIN1"
#define AIN2	"/AIN2"
#define AIN3	"/AIN3"
#define AIN4	"/AIN4"
#define AIN5	"/AIN5"
#define AIN6	"/AIN6"
#define AIN7	"/AIN7"

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
int setPWMPolarity(int helpnum, char* pin, int run);

//UART Prototypes
int initUART(int mgrnum, char* uartnum);
void closeUART(int fd);
int configUART(UART u, int property, char* value);
int txUART(int uart, unsigned char data);
unsigned char rxUART(int uart);
int strUART(int uart, char* buf);

//I2C Prototypes
int initI2C(int modnum, int addr);
void closeI2C(int device);
int writeByteI2C(int device, unsigned char *data);
int writeBufferI2C(int device, unsigned char *buf, int len);
int readByteI2C(int device, unsigned char *data);
int readBufferI2C(int device, int numbytes, unsigned char *buf);

//SPI Prototypes
int initSPI(int modnum);
void closeSPI(int device);
int writeByteSPI(int device,unsigned char *data);
int writeBufferSPI(int device, unsigned char *buf, int len);
int readByteSPI(int device, unsigned char *data);
int readBufferSPI(int device, int numbytes, unsigned char *buf);

//LCD 4-bit Prototypes
int initLCD();
int writeChar(unsigned char data);
int writeCMD(unsigned char cmd);
int writeString(char* str, int len);
int LCD_ClearScreen();
int LCD_Home();
int LCD_CR();
int LCD_Backspace();
int LCD_Move(int location);

//ADC Prototypes
int initADC(int mgrnum);
int readADC(int helpnum, char* ach);

//Time Prototypes
void pauseSec(int sec);
int  pauseNanoSec(long nano);

#endif
