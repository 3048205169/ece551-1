#include <stdio.h>
#include <stdlib.h>
#include <string.h>


//This function is used to figure out the ordering
//of the strings in qsort.  You do not need
//to modify it.
int stringOrder(const void * vp1, const void * vp2) {
  const char * const * p1 = vp1;
  const char * const * p2 = vp2;
  return strcmp(*p1, *p2);
}
//This function will sort and print data (whose length is count).
void sortData(char ** data, size_t count) {
  qsort(data, count, sizeof(char *), stringOrder);
}
void readfile(FILE *f){
  char ** array = NULL;
  char * line= NULL;
  size_t sz=0;
  int i =0;
  while(getline(&line,&sz,f)>=0){
    array=realloc(array,(i+1)*sizeof(*array));
    array[i]=line;
    line=NULL;
    i++;
  }
  free(line);
  sortData(array,i);
  for(int j=0;j<i;j++){
    printf("%s", array[j]);
    free(array[j]);
  }
  free(array);
}
int main(int argc, char ** argv) {
  
  //WRITE YOUR CODE HERE!
  if(argc==1){
    FILE *f=stdin;
    if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
    readfile(f);
    if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
    }
  }
  if(argc>1){
    for(int i=1;i<argc;i++){
      FILE * f = fopen(argv[i], "r");
      if (f == NULL) {
        perror("Could not open file");
        return EXIT_FAILURE;
      }
      readfile(f);    
      if (fclose(f) != 0) {
      perror("Failed to close the input file!");
      return EXIT_FAILURE;
      }
    }
  }
  else{
    perror("Failed to close the input file!");
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
  
}
