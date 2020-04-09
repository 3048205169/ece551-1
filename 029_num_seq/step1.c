// This file is for Step 1.
// You should do
//  Step 1 (A): write seq1
//  Step 1 (B): write main to test seq1
//  Step 1 (C): write printSeq1Range
//  Step 1 (D): add test cases to main to test printSeq1Range
//
// Be sure to #include any header files you need!
#include <stdio.h>
#include <stdlib.h>
int seq1(int x){
  int y=4*x-3;
  return y;
}
void test_seq1(int x){
  int y=seq1(x);
  printf("seq1(%d)=%d\n",x,y);
}
void printSeq1Range(int low, int high){
  
  for(int i=low;i<high;i++){
    int answer=seq1(i);
    if(i==low){
      printf("%d",answer);
    }
    else {
      printf(", %d",answer);
    }
   }
  printf("\n");
}
void test_printSeq1Range(int low, int high){
  printf("printSeq1Range(%d,%d)\n",low,high);
  printSeq1Range(low,high);
}
int main(){
  test_seq1(1);
  test_seq1(-1);
  test_seq1(0);
  test_seq1(123);
  test_seq1(2222232222);
  test_printSeq1Range(1,1);
  test_printSeq1Range(1,5);
  test_printSeq1Range(-3,6);
  test_printSeq1Range(-3,-5);
  test_printSeq1Range(6,10);
  test_printSeq1Range(-122,122);
  return 0;
}
