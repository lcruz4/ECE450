#include "motor.h"

void main(){
  initMotor();
  forward(40);
  sleep(1);
  backward(40);
  sleep(1);
  arc_left(40);
  sleep(1);
  arc_right(40);
  sleep(1);
  spin_right(40);
  sleep(1);
  spin_left(40);
  sleep(1);
  stop();
}
