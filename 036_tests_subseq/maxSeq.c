#include <stddef.h>
size_t maxSeq(int * array, size_t n){
  size_t answer=1;
  size_t i=0;
  size_t max=1;
  for(i=1;i<n;i++){
    if(array[i]>array[i-1]){
      answer++;
    }
    else{
      if(answer>max){
	max=answer;
      }
      answer=1;
    }
  }
  return answer;
}
