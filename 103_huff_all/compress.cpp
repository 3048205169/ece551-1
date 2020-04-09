#include <iostream>
#include <stdio.h>
#include <stdint.h>
#include <map>
#include <queue>
#include <assert.h>
#include <functional>
#include <stdlib.h>
#include "readFreq.h"
#include "node.h"



void writeHeader(BitFileWriter * bfw, const std::map<unsigned,BitString> &theMap) {
  for (int i =0 ; i < 257; i++) {
    std::map<unsigned,BitString>::const_iterator it = theMap.find(i);
    if (it != theMap.end()) {
      bfw->writeByte(it->second.size());
      bfw->writeBitString(it->second);
    }
    else {
      bfw->writeByte(0);
    }
  }
}

void writeCompressedOutput(const char* inFile,
			   const char *outFile,
			   const std::map<unsigned,BitString> &theMap ){
  BitFileWriter bfw(outFile);
  writeHeader(&bfw,theMap);

  //WRITE YOUR CODE HERE!
  //open the input file for reading
  FILE *f = fopen(inFile,"r");
  if(f==NULL){
    std::cerr<<"Reading Error"<<"\n";
  }
  //You need to read the input file, lookup the characters in the map,
  //and write the proper bit string with the BitFileWriter
  int c;
  while((c=fgetc(f))!=EOF){
    unsigned temp=(unsigned) c;
    if(theMap.find(temp)!=theMap.end()){
      bfw.writeBitString(theMap.find(temp)->second);
    }
    else{
      std::cerr<<"char not find"<<"\n";
    }
  }
  bfw.writeBitString(theMap.find(256)->second);
  //dont forget to lookup 256 for the EOF marker, and write it out.
  fclose(f);
  //BitFileWriter will close the output file in its destructor
  //but you probably need to close your input file.
}

int main(int argc, char ** argv) {
  if (argc != 3) {
    fprintf(stderr,"Usage: compress input output\n");
    return EXIT_FAILURE;
  }
  //WRITE YOUR CODE HERE
  //Implement main
  //hint 1: most of the work is already done. 
  //hint 2: you can look at the main from the previous tester for 90% of this

  uint64_t * freq = readFrequencies(argv[1]);
  Node * root = buildTree(freq);
  std:: map<unsigned, BitString> mp;
  BitString b;
  root->buildMap(b, mp);
  writeCompressedOutput(argv[1], argv[2], mp);
  delete[] freq;
  delete root;
  return EXIT_SUCCESS;
  }
