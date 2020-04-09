#include <stdio.h>
#include <stdlib.h>
unsigned power(unsigned x,unsigned y);
void run_check(unsigned x,unsigned y, unsigned expected_ans){
  if(power(x,y)!=expected_ans){
    printf("there is a filure");
    exit(EXIT_FAILURE);
  }
}
int main(void){
  run_check(1,1,1);
  run_check(0,0,1);
  run_check(1,2,1);
  run_check(2,2,4);
  run_check(1,0,1);
  run_check(44445444,1,44445444);
  run_check(3,3,27);
  return EXIT_SUCCESS;
}

