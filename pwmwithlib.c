#include <unistd.h>
#include <fcntl.h>
#include "motor.h"

int buffer[2];		// counter tracking the wheel encoder
int flag = 0;		// indicates when the wheel encoder detects a rotor
int pid = 0;
int IRsensorFront = 0;

void main(){
	int ret;
	initPin(67);
	setPinDirection(67, IN);				//P8_8 set to input mode
	initMotor();
	int c1;
    	c1 = analog_read(1);
   	printf("c1:%d\n\n",c1);
	ret = pipe2(buffer, O_NONBLOCK);
	
	// begin path

	if((pid = fork()) != 0){
		int tick = 0;
		int counter = 0;
		while(1){
			tick = getPinValue(67);
			if(tick == 1){
				counter += 1;
				read(buffer[1],NULL,sizeof(int));
				write(buffer[1],&counter, sizeof(int));
			}
			//usleep(1);
			//Maybe put a small sleep so it's not getting the pin value so much
		}
	}
	else{
		int oldcount = 0;
		int counter = 0;
		while (counter-oldcount < 3500){
			forward(40);
			read(buffer[0],&counter,sizeof(int));
			printf("%d\n",counter);
			}
		spin_right(40);
		usleep(840000);	//assumed turn duration
		printf("Check Point A");
		read(buffer[0],&oldcount,sizeof(int));
		while (counter-oldcount < 4500){//should counter be reset?
			read(buffer[0],&counter,sizeof(int));
			printf("%d\n",counter);
			if (counter - oldcount == 2000 ){
				//spin_right(40);
				//usleep(10000);
			}
			printf("%d\n",counter);
			forward(40);
			}
		spin_right(30);
		usleep(1150000);	//assumed turn duration
		printf("Check Point B");
		//Here is where you wanted to include the Wall Follower code
		read(buffer[0],&oldcount,sizeof(int));
		while (counter-oldcount < 6550){
			read(buffer[0],&counter,sizeof(int));
			printf("%d\n",counter);
			if (counter - oldcount == 5500){//  ||  counter - oldcount == 4000 ){
				//spin_right(40);
				//usleep(150000);
			}
			forward(40);
		}
		spin_right(30);
		usleep(1210000);	//assumed turn duration
		printf("Check Point D");

		read(buffer[0],&oldcount,sizeof(int));
		while (counter-oldcount < 24000){
			read(buffer[0],&counter,sizeof(int));
			forward(40);
			}
		spin_right(40);
		usleep(860000);	//assumed turn duration
		printf("Check Point D");
		//This marks the end of the path
		read(buffer[0],&oldcount,sizeof(int));
		while (counter-oldcount < 3600){
			read(buffer[0],&counter,sizeof(int));
			printf("%d\n",counter);
			forward(40);
		}
		
			
		stop();
		exit(0);

		if(IRsensorFront > .5){	//detect object directly in front of bot perform 360 & stop
			spin_left(40);
			sleep(1.2);
		}
			stop();
	}
}
