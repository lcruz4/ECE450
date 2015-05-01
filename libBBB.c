/*Copyright (C) 2013 Gavin Strunk

Permission is hereby granted, free of charge, to any person obtaining a copy of this software $

The above copyright notice and this permission notice shall be included in all copies or subst$

THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING $
*/


#include "libBBB.h"

//Local functions not used by outside world
int checkOverlay(char *file);
void initCMD(unsigned char cmd);

//*************************************************
//*            Device Tree Overlay                *
//*************************************************
int addOverlay(char *dtb, char *overname)
{
        char file[100];

        sprintf(file,"/lib/firmware/%s",dtb);

        printf("Check for dtbo file: ");
        if(checkOverlay(file) == 0)
        {
                //check current directory for file
                char temp[100];
                sprintf(temp,"%s",dtb);

                if((access(temp,F_OK)) < 0)
                {
                        printf("The file isn't here either\n");
                        exit(1);
                }
                else
                {
                        printf("Found file\n");
                        printf("Copying to correct folder\n");

                        FILE *f,*fnew;
                        long num;
                        char *fileread;
                        size_t result;

                        f = fopen(temp,"r");
                        if(f == NULL)
                        {
                                printf("temp failed to open\n");
                                exit(1);
                        }

                        fnew = fopen(file,"w");
                        if(fnew == NULL)
                        {
                                printf("file failed to open\n");
                                exit(1);
                        }

                        fseek(f,0,SEEK_END);
                        fseek(fnew,0,SEEK_SET);
                        num = ftell(f);
                        rewind(f);

                        fileread = (char*) malloc(sizeof(char)*num);
                        if(fileread == NULL)
                        {
                                printf("Memory error\n");
                                exit(1);
                        }

                        result = fread(fileread,1,num,f);
                        if(result != num)
                        {
                                printf("Error reading file\n");
                                exit(1);
                        }

                        fwrite(fileread,sizeof(char),sizeof(fileread),fnew);
                        fclose(f);
                        fclose(fnew);

                        //Now file should be there so double check
                        if(checkOverlay(file) == 0)
                        {
                                printf("This just isn't working\n");
                                exit(1);
                        }
                        }
                }

        }

        //If you made it here then the dtbo file exists now we need to check
        //if it is already applied or not, then add it if it isn't there, or
        //if it is already applied then we did all of this for nothing

        FILE *over;
        char ch[200] = {0};
        const char *pch = &ch[0];
        char *search;
        int ch2 = 0;
        int j;
        //char strsearch[] = "uart";

        over = fopen("/sys/devices/bone_capemgr.8/slots", "r");
        if(over == NULL)
        {
                printf("File didn't open\n");
                exit(1);
        }

        fseek(over,0,SEEK_SET);

        while(ch2 != -1)
        {
                //find all the overlays
                j = 0;
                while(ch2 != '\n')
                {
                        ch2 = fgetc(over);
                        if(ch2 == '\n')
                                break;
                        ch[j] = (char) ch2;
                        j++;
                }

                printf("%s\n",ch);

                //now look for the specific overlay
                search = strstr(pch,overname);
                if(search == NULL)
                {
                        printf("Search: Failed\n");
                }
                else
                {
                        printf("Search: Found\n");
                        return 0;
                }

                ch2 = fgetc(over);

        }

        fclose(over);

        //ok if you made it here then you search them all and it would
        //appear that it isn't there, so it is now time to add it
        char name[100];
        sprintf(name, "%s",overname);

        over = fopen("/sys/devices/bone_capemgr.8/slots", "w");
        if(over == NULL) printf("File didn't open\n");
        fseek(over,0,SEEK_SET);
        fprintf(over,name);
        fflush(over);
        fclose(over);

        printf("Overlay Added\n");
        return 0;
}

int checkOverlay(char *file)
{
        int found = 0;

        if((access(file,F_OK)) < 0)
        {
                printf("Failed\n");
                found = 0;
        }
        else
        {
                printf("Success\n");
                found = 1;
        }
        return found;
}

//*************************************************
//*                USR FUNCTIONS                  *
//*************************************************
int setUsrLedValue(char* led, int value)
{
        FILE *usr;
        char buf[20];
        char buf2[50] = "/sys/class/leds/beaglebone:green:";

        //build file path to usr led brightness
        sprintf(buf,"%s",led);
        strcat(buf2,strcat(buf,"/brightness"));

        usr = fopen(buf2, "w");
        if(usr == NULL) printf("USR Led failed to open\n");
        fseek(usr,0,SEEK_SET);
        fprintf(usr,"%d",value);
        fflush(usr);
        fclose(usr);

        return 0;
}

//*************************************************
//*               GPIO FUNCTIONS                  *
//*************************************************
int initPin(int pinnum)
{
        FILE *io;

        io = fopen("/sys/class/gpio/export", "w");
        if(io == NULL) printf("Pin failed to initialize\n");
        fseek(io,0,SEEK_SET);
        fprintf(io,"%d",pinnum);
        fflush(io);
        fclose(io);

        return 0;
}

int setPinDirection(int pinnum, char* dir)
{
        FILE *pdir;
        char buf[10];
        char buf2[50] = "/sys/class/gpio/gpio";

        //build file path to the direction file
        sprintf(buf,"%i",pinnum);
        strcat(buf2,strcat(buf,"/direction"));

        pdir = fopen(buf2, "w");
        if(pdir == NULL) printf("Direction failed to open\n");
        fseek(pdir,0,SEEK_SET);
        fprintf(pdir,"%s",dir);
        fflush(pdir);
        fclose(pdir);

        return 0;
}

int setPinValue(int pinnum, int value)
{
        FILE *val;
        char buf[5];
        char buf2[50] = "/sys/class/gpio/gpio";

        //build path to value file
        sprintf(buf,"%i",pinnum);
        strcat(buf2,strcat(buf,"/value"));

        val = fopen(buf2, "w");
        if(val == NULL) printf("Value failed to open\n");
        fseek(val,0,SEEK_SET);
        fprintf(val,"%d",value);
        fflush(val);
        fclose(val);

        return 0;
}

int getPinValue(int pinnum)
{
        FILE *val;
        int value;
        char buf[5];
        char buf2[50] = "/sys/class/gpio/gpio";

        //build file path to value file
        sprintf(buf,"%i",pinnum);
        strcat(buf2,strcat(buf,"/value"));

        val = fopen(buf2, "r");
        if(val == NULL) printf("Input value failed to open\n");
        fseek(val,0,SEEK_SET);
        fscanf(val,"%d",&value);
        fclose(val);

        return value;
}

//*************************************************
//*                PWM FUNCTIONS                  *
//*************************************************
int initPWM(int mgrnum, char* pin)
{
        FILE *pwm;
        char buf[5];
        char buf2[50] = "/sys/devices/bone_capemgr.";
        char buf3[20] = "bone_pwm_";

        //build file paths
        sprintf(buf,"%i",mgrnum);
        strcat(buf2,strcat(buf,"/slots"));

        strcat(buf3,pin);

        pwm = fopen(buf2, "w");
        if(pwm == NULL) printf("PWM failed to initialize\n");
        fseek(pwm,0,SEEK_SET);
        fprintf(pwm,"am33xx_pwm");
        fflush(pwm);
        fprintf(pwm,"%s",buf3);
        fflush(pwm);
        fclose(pwm);

        return 0;
}

int setPWMPeriod(int helpnum, char* pin, int period)
{
        FILE *pwm;
        char buf[5];
        char buf2[60] = "/sys/devices/ocp.3/pwm_test_";

        //build file path
        sprintf(buf,"%i",helpnum);
        printf("%s\n",pin);
        strcat(buf2,pin);
        strcat(buf2,".");
        strcat(buf2,strcat(buf,"/period"));

        printf("%s\n",buf2);
        pwm = fopen(buf2, "w");
        if(pwm == NULL) printf("PWM Period failed to open\n");
        fseek(pwm,0,SEEK_SET);
        fprintf(pwm,"%d",period);
        fflush(pwm);
        fclose(pwm);

        return 0;
}

int setPWMDuty(int helpnum, char* pin, int duty)
{
        FILE *pwm;
        char buf[5];
        char buf2[50] = "/sys/devices/ocp.3/pwm_test_";

        //build file path
        sprintf(buf,"%i",helpnum);
        strcat(buf2,pin);
        strcat(buf2,".");
        strcat(buf2,strcat(buf,"/duty"));

        pwm = fopen(buf2, "w");
        if(pwm == NULL) printf("PWM Duty failed to open\n");
        fseek(pwm,0,SEEK_SET);
        fprintf(pwm,"%d",duty);
        fflush(pwm);

        return 0;
}

int setPWMOnOff(int helpnum, char* pin, int run)
{
        FILE *pwm;
        char buf[5];
        char buf2[50] = "/sys/devices/ocp.3/pwm_test_";

        //build file path
        sprintf(buf,"%i",helpnum);
        strcat(buf2,pin);
        strcat(buf2,".");
        strcat(buf2,strcat(buf,"/run"));

        pwm = fopen(buf2, "w");
        if(pwm == NULL) printf("PWM Run failed to open\n");
        fseek(pwm,0,SEEK_SET);
        fprintf(pwm,"%d",run);
        fflush(pwm);
        fclose(pwm);

        return 0;
}

//*************************************************
//*                SPI FUNCTIONS                  *
//*************************************************
int initSPI(int modnum)
{
        int device;

        device = open("/dev/spidev1.0", O_RDWR);
        if(device < 0)
        {
                printf("SPI file failed to open\n");
                return -1;
        }

        return device;
}

void closeSPI(int device)
{
        close(device);
}

int writeByteSPI(int device, unsigned char* data)
{
        if(write(device, data, 1) != 1)
        {
                printf("Error occurred during SPI write\n");
                return -1;
        }

        return 0;
}

int writeBufferSPI(int device, unsigned char *buf, int len)
{
        if(write(device, buf, len) != len)
        {
                printf("Error occurred during buffer SPI write\n");
                return -1;
        }

        return 0;
}

int readByteSPI(int device, unsigned char* data)
{
        if(read(device, &data, 1) != 1)
        {
                printf("Error occurred during SPI read\n");
                return -1;
        }
        return 0;
}

int readBufferSPI(int device, int numbytes, unsigned char *buf)
{
        if(read(device, &buf, numbytes) != numbytes)
        {
                printf("Error occurred during buffer SPI read\n");
                return -1;
        }
        return 0;
}

//*************************************************
//*                ADC FUNCTIONS                  *
//*************************************************
int initADC(int mgrnum)
{
        FILE *ain;
        char buf[5];
        char buf2[50] = "/sys/devices/bone_capemgr.";

        //build path to setup ain
        sprintf(buf,"%i",mgrnum);
        strcat(buf2,strcat(buf,"/slots"));

        ain = fopen(buf2, "w");
        if(ain == NULL) printf("Analog failed load\n");
        fseek(ain,0,SEEK_SET);
        fprintf(ain,"cape-bone-iio");
        fflush(ain);
        fclose(ain);

        return 0;
}

int readADC(int helpnum, char* ach)
{
        FILE *aval;
        int value;
        char buf[5];
        char buf2[50] = "/sys/devices/ocp.3/helper.";

        //build file path to read adc
        sprintf(buf,"%i",helpnum);
        strcat(buf2,strcat(buf,ach));
        aval = fopen(buf2, "r");
        if(aval == NULL) printf("Analog failed to open\n");
        fseek(aval,0,SEEK_SET);
        fscanf(aval,"%d",&value);
        fflush(aval);
        fclose(aval);

        return value;
}

//********************************************
//*            TIME FUNCTIONS                *
//********************************************
void pauseSec(int sec)
{
        time_t now,later;

        now = time(NULL);
        later = time(NULL);

        while((later - now) < (double)sec)
                later = time(NULL);
}

int pauseNanoSec(long nano)
{
        struct timespec tmr1,tmr2;

        //assume you are not trying to pause more than 1s
        tmr1.tv_sec = 0;
        tmr1.tv_nsec = nano;

        if(nanosleep(&tmr1, &tmr2) < 0)
        {
                printf("Nano second pause failed\n");
                return -1;
        }
        return 0;
}

void speed(int speed, int helpnum){
    int vel = 0;
    vel = ((float)speed*.01)*(int)200000000;
//Back Right Wheel
        setPWMPeriod(helpnum, P8_13, 200000000);
        setPWMDuty(helpnum, P8_13, vel);
        setPWMOnOff(helpnum, P8_13, ON);

//Front Right Wheel
        setPWMPeriod(16, P9_14, 200000000);
        setPWMDuty(16, P9_14, vel);
        setPWMOnOff(16, P9_14, ON);

//Back Left Wheel
        setPWMPeriod(17, P8_18, 200000000);
        setPWMDuty(17, P8_18, vel);
        setPWMOnOff(17, P8_18, ON);

//Front Left Wheel
        setPWMPeriod(18, P9_16, 200000000);
        setPWMDuty(18, P9_16, vel);
        setPWMOnOff(18, P9_16, ON);
}

void turn_right(){
    setPinValue(45, 1);         //left wheels
    setPinValue(60, 0);         //right wheels
}

void forward(){
    initPin(45);
    setPinValue(45, 1);         //left wheels
    initPin(60);
    setPinValue(60, 1);         //right wheels
}