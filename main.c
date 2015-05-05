#include "libBBB.h"
#include <time.h>

main(){
	clock_t t;
	int val;

	initPin(67);
	setPinDirection(67,IN);
	t = clock();
	while(1){
		val = getPinValue(67);
		if(val==1) printf("1\n");
		t = clock() - t;
		printf("time:%f\n",((float)t)/CLOCKS_PER_SEC);
	}
}
