#include<stdio.h>
#include<stdlib.h>
#include <ctype.h>
int max(int *myArray){
  int temp=0;
  int c=0;
  for(int i=0;i<26;i++){
    if(myArray[i]>temp){
      temp=myArray[i];
      c=i;
    }
  }
  return (c+22)%26;
}
int break_key(FILE *f){
  int temp[26]={0};
  int c;
  while((c=fgetc(f))!=EOF){
    if(isalpha(c)){
      c=tolower(c);
      temp[c-'a']++;
    }
  }
  int key=max(temp);
  return key;
}
int main(int argc, char ** argv){
  if (argc != 2) {
    fprintf(stderr,"Usage: encrypt key inputFileName\n");
    return EXIT_FAILURE;
  }
  FILE * f=fopen(argv[1],"r");
  if (f == NULL) {
    perror("Could not open file");
    return EXIT_FAILURE;
  }
  int key= break_key(f);
  printf("%d\n", key);
  if (fclose(f) != 0) {
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
