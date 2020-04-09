#include "node.h"
void Node::buildMap(BitString b, std::map<unsigned,BitString> & theMap) {
  //WRITE ME!
  if(sym != NO_SYM){
    theMap[sym]=b;
  }
  else{
    assert(left != NULL && right != NULL);
    BitString b1=b.plusZero();
    BitString b2=b.plusOne();
    left->buildMap(b1,theMap);
    right->buildMap(b2,theMap);
  }
}

