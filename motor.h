#include "libBBB.h"
#include <dirent.h>
#include "spi.h"
#define MGRNUM	9

int helper(char*);
void initMotor();
void forward(int);
void backward(int);
void arc_left(int);
void arc_right(int);
void spin_left(int);
void spin_right(int);
void speed(int);
void stop();
