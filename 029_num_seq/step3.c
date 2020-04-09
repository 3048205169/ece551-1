// This file is for Step 3.
// You should do
//  Step 3 (A): write seq3
//  Step 3 (B): write main to test seq3
//  Step 3 (C): write countEvenInSeq3Range
//  Step 3 (D): add test cases to main to test countEvenInSeq3Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
int seq3(int x,int y){
  int answer=(y-3)*(x+2)+6;
  return answer;
}
void test_seq3(int x,int y){
  int answer=seq3(x,y);
  printf("seq3(%d, %d) = %d\n",x,y,answer);
}
int countEvenInSeq3Range(int xLow,int xHi,int yLow,int yHi){
  int answer=0;
  for(int i=xLow;i<xHi;i++){
    for(int j=yLow;j<yHi;j++){
      int temp=seq3(i,j);
      if(temp%2==0){
	answer++;
      }
    }
  }
  return answer;
}
void test_countEvenInSeq3Range(int xLow,int xHi,int yLow,int yHi){
    int answer;
    answer=countEvenInSeq3Range(xLow,xHi,yLow,yHi);
    printf("countEvenInSeq3Range(%d, %d, %d, %d) = %d\n",xLow,xHi,yLow,yHi,answer);
  }
int main(){
  test_seq3(1,1);
  test_seq3(1,3);
  test_seq3(-1,-5);
  test_seq3(33,444);
  test_countEvenInSeq3Range(0,2,0,3);
  test_countEvenInSeq3Range(0,0,0,0);
  test_countEvenInSeq3Range(1,3,1,3);
  test_countEvenInSeq3Range(-1,3,-2,7);
  test_countEvenInSeq3Range(-1,4,4,8);
  test_countEvenInSeq3Range(1,0,1,0);
  test_countEvenInSeq3Range(0,2,0,3);
  

  return 0;
  
}
