/** SPI C Transfer Example, Written by Derek Molloy (www.derekmolloy.ie)
*    for the book Exploring BeagleBone. Based on the spidev_test.c code
*    example at www.kernel.org
*
* Written by Derek Molloy for the book "Exploring BeagleBone: Tools and 
* Techniques for Building with Embedded Linux" by John Wiley & Sons, 2014
* ISBN 9781118935125. Please see the file README.md in the repository root 
* directory for copyright and GNU GPLv3 license information.            */

#include<stdio.h>
#include<fcntl.h>
#include<unistd.h>
#include<sys/ioctl.h>
#include<stdint.h>
#include<time.h>
#include<linux/spi/spidev.h>

#define SPI_PATH "/dev/spidev1.0"

int transfer(int fd, unsigned char send[], unsigned char receive[], int length){
   struct spi_ioc_transfer transfer;           //the transfer structure
   transfer.tx_buf = (unsigned long) send;     //the buffer for sending data
   transfer.rx_buf = (unsigned long) receive;  //the buffer for receiving data
   transfer.len = length;                      //the length of buffer
   transfer.speed_hz = 1000000;                //the speed in Hz
   transfer.bits_per_word = 8;                 //bits per word
   transfer.delay_usecs = 0;                   //delay in us

   // send the SPI message (all of the above fields, inc. buffers)
   int status = ioctl(fd, SPI_IOC_MESSAGE(1), &transfer);
   if (status < 0) {
      perror("SPI: SPI_IOC_MESSAGE Failed");
      return -1;
   }
   return status;
}

int analog_read(uint8_t channel){
   unsigned int fd;  //file handle and loop counter
   uint8_t sendbuf[3];
   unsigned char recvbuf[3];
   uint8_t bits = 8, mode = 0;             //8-bits per word, SPI mode 3
   uint32_t speed = 1000000;               //Speed is 1 MHz
   // The following calls set up the SPI bus properties
   if ((fd = open(SPI_PATH, O_RDWR))<0){
      perror("SPI Error: Can't open device.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_MODE, &mode)==-1){
      perror("SPI: Can't set WR SPI mode.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_MODE, &mode)==-1){
      perror("SPI: Can't get RD SPI mode.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits)==-1){
      perror("SPI: Can't set WR bits per word.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits)==-1){
      perror("SPI: Can't get RD bits per word.");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed)==-1){
      perror("SPI: Can't set max speed HZ");
      return -1;
   }
   if (ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed)==-1){
      perror("SPI: Can't get max speed HZ.");
      return -1;
   }

   // Check that the properties have been set

   // Loop from 0 to 255 and light the LED bar as a binary counter
   sendbuf[0] = 1; sendbuf[1] = (8+channel)<<4; sendbuf[2] = 0;
   if (transfer(fd, (unsigned char *) sendbuf, recvbuf, 3)==-1){
     perror("Failed to update the display");
   return -1;
   }
   printf("recvbuf:[%d,%d,%d]\n",recvbuf[0],recvbuf[1],recvbuf[2]);
   close(fd);               //close the file
   return ((recvbuf[1]&3)<<8)+recvbuf[2];
}

void main(){
  int c0,c1,c2;
  while(1){
    c0 = analog_read(0);
    c1 = analog_read(1);
    c2 = analog_read(2);
    printf("c0:%d\nc1:%d\nc2:%d\n\n",c0,c1,c2);
    sleep(1);
  }
}
