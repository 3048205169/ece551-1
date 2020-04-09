#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "kv.h"
void error(void){
  fprintf(stderr, "Error\n");
  exit(EXIT_FAILURE);
}
void readStr(char * str,kvpair_t *kvPair){
  char * p;
  char * q;
  p=strchr(str,'=');
  if(p==NULL){
    error();
  }
  kvPair->key=strndup(str,p-str);
  q=strchr(p++,'\n');
  if(q==NULL){
    error();
  }
  kvPair->value=strndup(p,q-p);
}

kvarray_t * readKVs(const char * fname) {
  //WRITE ME
  FILE *f=fopen(fname,"r");
  char *curr = NULL;
  size_t size=0;
  size_t i=0;
  kvpair_t *kvPair;
  kvarray_t *kv;
  kvPair=malloc(sizeof(*kvPair));
  if(f==NULL){
    printf("Fail to open file");
    return NULL;
  }
  
  while(getline(&curr,&size,f)!= -1){
    kvPair=realloc(kvPair,(i+1)*sizeof(*kvPair));
    if(kvPair==NULL){
      error();
    }
    readStr(curr,&kvPair[i]);
    i++;
  }
  free(curr);
  fclose(f);
  kv=malloc(sizeof *kv);
  if(kv==NULL){
    error();
  }
  kv->kvArray=kvPair;
  kv->numKv=i;
  return kv;
  
}

void freeKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t i;
  for(i=0;i<pairs->numKv;i++){
    free(pairs->kvArray[i].key);
    free(pairs->kvArray[i].value);
  }
  free(pairs->kvArray);
  free(pairs);
  
}

void printKVs(kvarray_t * pairs) {
  //WRITE ME
  size_t i;
  kvpair_t *p;
  for(i=0;i<pairs->numKv;i++){
    p=&(pairs->kvArray[i]);
    printf("key = '%s' value = '%s'\n", p->key, p->value);
  }
}

char * lookupValue(kvarray_t * pairs, const char * key) {
  //WRITE ME
  size_t i;
  kvpair_t *p;
  for(i=0;i<pairs->numKv;i++){
    p=&(pairs->kvArray[i]);
    if(strcmp(key,p->key)==0){
      return p->value;
    }
    
  }
  return NULL;
}
