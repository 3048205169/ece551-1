#include "IntMatrix.h"

IntMatrix::IntMatrix():numRows(0),numColumns(0),rows(NULL){
}
IntMatrix::IntMatrix(int r, int c):numRows(r), numColumns(c) {
  rows=new IntArray *[r];
  for(int i=0;i<r;i++){
    rows[i]=new IntArray(c);
  }
}
IntMatrix::IntMatrix(const IntMatrix & rhs):numRows(rhs.numRows),numColumns(rhs.numColumns)  {
  rows=new IntArray *[rhs.numRows];
  for(int i=0;i<rhs.numRows;i++){
    rows[i]= new IntArray(rhs.numColumns);
    *rows[i] = *rhs.rows[i];
  }
}
IntMatrix::~IntMatrix() {
  for(int i=0;i<numRows;i++){
    delete  rows[i];
  }
  delete[] rows;
}
IntMatrix &IntMatrix::operator=(const IntMatrix & rhs) {
  if(this !=&rhs){
    //pay attention to!
    IntArray ** temp = new IntArray *[rhs.numRows];
    for(int i=0;i<rhs.numRows;i++){
      temp[i]=new IntArray(rhs.numColumns);
      *temp[i]=*rhs.rows[i];
    }
    for(int i = 0; i < numRows; i++){
      delete rows[i];
    }
    delete[] rows;
    numRows=rhs.numRows;
    numColumns=rhs.numColumns;
    rows=temp;
  }
  return *this;
}
int IntMatrix::getRows() const {
  return numRows;
}
int IntMatrix::getColumns() const {
  return numColumns;
}
const IntArray & IntMatrix::operator[](int index) const {
  assert(index>=0 && index<numRows);
  return *rows[index];
}
IntArray & IntMatrix::operator[](int index){
  assert(index>=0 && index<numRows);
  return *rows[index];
}



bool IntMatrix::operator==(const IntMatrix & rhs) const {
  if(numRows==rhs.numRows && numColumns==rhs.numColumns){
    for(int i=0;i<numRows;i++){
      if(*rows[i]!=*rhs.rows[i]){
	return 0;
      }
    }
  }
  else{
    return 0;
  }
  return 1;
}

IntMatrix IntMatrix::operator+(const IntMatrix & rhs) const {
  assert(numRows == rhs.numRows && numColumns == rhs.numColumns);
  IntMatrix a( numRows,numColumns);
  for(int i=0;i<numRows;i++){
    for(int j=0;j<numColumns;j++){
      (*a.rows[i])[j]=(*rows[i])[j]+(*rhs.rows[i])[j];
    }
  }
  return a;
}

std::ostream & operator<<(std::ostream & s, const IntMatrix & rhs) {
  if(rhs.getRows() == 0){
    s<<"[  ]";
    return s;
  }
  s<<"[ ";
  for(int i = 0; i < rhs.getRows()-1; i++){
    s<<rhs[i]<<",\n";
  }
  s<<rhs[rhs.getRows()-1]<<" ]";
  return s;
}
