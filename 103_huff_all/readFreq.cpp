#include <stdio.h>
#include <cstdlib>
#include "readFreq.h"
#include <iostream>
void printSym(std::ostream & s, unsigned sym) {
  if (sym > 256 ) {
    s << "INV";
  }
  else if (sym == 256) {
    s << "EOF";
  }
  else if (isprint(sym)) {
    char c = sym;
    s << "'" << c << "'";
  }
  else {
    std::streamsize w = s.width(3);
    s << std::hex << sym << std::dec;
    s.width(w);
  }
}
uint64_t * readFrequencies(const char * fname) {
  //WRITE ME!
  uint64_t * ans=new uint64_t[257];
  for(int i=0;i<257;i++){
    ans[i]=0;
  }
  FILE *p=fopen(fname,"r");
  if(p==NULL){
    std::cerr<<"Reading Error"<<"\n";
  }
  else{
    int c;
    while((c=fgetc(p))!=EOF){
      ans[c]++;
    }
  }
  ans[256]++;
  fclose(p);
  return ans;
}
