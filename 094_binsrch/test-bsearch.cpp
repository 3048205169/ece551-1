#include<cstdio>
#include"function.h"
#include<cmath>
#include<iostream>
class CountedIntFn : public Function<int,int>{
protected:
  unsigned remaining;
  Function<int,int> * f;
  const char * mesg;
public:
  CountedIntFn(unsigned n, Function<int,int> * fn, const char * m): remaining(n),
                                                                    f(fn),
								    mesg(m) {}
  virtual int invoke(int arg) {
    if (remaining == 0) {
      fprintf(stderr,"Too many function invocations in %s\n", mesg);
      exit(EXIT_FAILURE);
    }
    remaining--;
    return f->invoke(arg);
  }

};
class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};
int binarySearchForZero(Function<int, int> * f, int low, int high);

void check(Function<int,int> * f,
           int low,
	   int high,
	   int expected_ans,
	   const char * mesg){
  unsigned n;
  if(high>low){
    n=log2(high-low)+1;
  }
  else{
    n=1;
  }
CountedIntFn *function=new CountedIntFn(n,f,mesg);
  int ans = binarySearchForZero(function,low,high);
  if(ans!=expected_ans){
    fprintf(stderr, "Wrong output answer in %s\n", mesg);
    exit(EXIT_FAILURE);
  }
}

int main() {
  SinFunction * sinFunc = new SinFunction();

  check(sinFunc, 1, 500, 499, "sinfunc1");
  check(sinFunc, 70000, 90000, 70000, "sinfunc2");
  check(sinFunc, 52359, 100000, 52359, "sinfunc3");
  check(sinFunc, 0, 52359, 52358, "sinfunc4");
  check(sinFunc, -1, -1, -1, "sinfunc5");
  check(sinFunc, 52359, 52359, 52359, "sinfunc6");
  check(sinFunc, 99, 99, 99, "sinfunc7");
  check(sinFunc, 60000, 60000, 60000, "sinfunc8");
  check(sinFunc, 1, 52359, 52358, "sinfunc9");
  check(sinFunc, 0, 150000, 52359, "sinfunc11");
  check(sinFunc, 0, 150000, 52359, "sinfunc11");
  check(sinFunc, 0, 104717, 52359, "sinfunc11");
  return 0;
}
