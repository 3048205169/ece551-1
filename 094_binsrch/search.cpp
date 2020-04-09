#include "function.h"
#include<cstdlib>
#include<cmath>
class SinFunction : public Function<int, int> {
public:
  virtual int invoke(int arg) {
    return 10000000 * (sin(arg/100000.0) - 0.5);
  }
};

int binarySearchForZero(Function<int, int> * f, int low, int high){
  while((high-low)>1){
    int temp=low+(high-low)/2;
    int ans=f->invoke(temp);
    if(ans > 0){
      high=temp;
    }
    else if(ans==0){
      return temp;
    }
    else{
      low=temp;
    }
  }
  return low;
}
