#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "outname.h"

char * computeOutputFileName(const char * inputName) {
  //WRITE ME
  char * temp;
  temp=malloc((strlen(inputName)+8)*sizeof(*temp));
  size_t i=0;
  char * head=temp;
  while(*inputName!='\0'){
    *temp=*inputName;
    temp++;
    inputName++;
  }
  temp[i]='.';
  temp[i+1]='c';
  temp[i+2]='o';
  temp[i+3]='u';
  temp[i+4]='n';
  temp[i+5]='t';
  temp[i+6]='s';
  temp[i+7]='\0';
  return head;
}
