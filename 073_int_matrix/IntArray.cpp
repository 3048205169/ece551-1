#include "IntArray.h"
#include <cstdlib>
#include <iostream>
#include<assert.h>
//default constructor
IntArray::IntArray():data(NULL),numElements(0){}
//overload constructor
IntArray::IntArray(int data):data(new int[data]),numElements(data){}
//copy constructor
IntArray::IntArray(const IntArray & rhs):data(new int[rhs.numElements]),numElements(rhs.numElements){
  for(int i=0;i<numElements;i++){
    data[i]=rhs.data[i];
  }
}
//assignment constructor
IntArray & IntArray::operator =(const IntArray &rhs){
  if(this !=&rhs){
    int *temp=new int[rhs.numElements];
    for(int i=0;i<rhs.numElements;i++){
      temp[i]=rhs.data[i];
    }
    delete []data;
    data=temp;
    numElements=rhs. numElements;
  }
  return *this;
}
//destructor
IntArray:: ~IntArray(){
  delete [] data;
}
//[] operator
int & IntArray::operator [](int index){
  assert(index>=0 && index<numElements);
  return data[index];
}
const int & IntArray::operator [](int index) const{
  assert(index>=0 && index<numElements);
  return data[index];
}
//size
int IntArray::size() const{
  return numElements;
}
//== operator
bool IntArray::operator ==(const IntArray &rhs) const{
  if(numElements!=rhs.numElements){
    return 0;
  }
  for(int i=0;i<numElements;i++){
    if(data[i]!=rhs.data[i]){
      return 0;
    }
  }
  return 1;
}
//!=
bool IntArray::operator	!=(const IntArray &rhs) const{
  return !((*this)==rhs);
}

//<<
std::ostream & operator <<(std::ostream &s, const IntArray &rhs) {
  if(rhs.size()<=0){
    s<<"{}";
  }
  else{
    s<<"{";
    for(int i=0;i<rhs.size()-1;i++){
      s<<rhs[i]<<",";
    }
    s<<rhs[rhs.size()-1]<<"}";
  }
  return s;
}
