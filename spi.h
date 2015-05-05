#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<time.h>
#include<linux/spi/spidev.h>

int transfer(int, unsigned char[], unsigned char[], int);
int analog_read(uint8_t);
