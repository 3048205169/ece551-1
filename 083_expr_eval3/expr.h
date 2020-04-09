#include <cstdlib>
#include<sstream>
class Expression
{
 public:
  virtual std::string toString() const = 0;
  virtual long evaluate() const =0;
  virtual ~Expression() {}
};

class NumExpression : public Expression{
 private:
  long num;
 public:
 NumExpression(long w):num(w){}
  virtual long evaluate() const{
    return num;
  }
  virtual std::string toString() const{
    std::string temp;
    std::stringstream ss;
    ss<<num;
    temp=ss.str();
    return temp;
  }
  virtual ~NumExpression(){};
};

class CalculationExpression :public Expression{
 protected:
  std::string exp1;
  std::string exp2;
  long i1;
  long i2;
 public:
 CalculationExpression(Expression *lhs, Expression *rhs):exp1(lhs->toString()),exp2(rhs->toString()),i1(lhs->evaluate()),i2(rhs->evaluate()){
    delete lhs;
    delete rhs;
  }
  virtual std::string toString() const =0;
  virtual ~CalculationExpression(){};

};

class MinusExpression :public CalculationExpression{
 public:
 MinusExpression(Expression *lhs, Expression *rhs):CalculationExpression(lhs,rhs){}
  virtual long evaluate() const{
    return i1-i2;
  }
  virtual std::string toString() const{
    std::string temp;
    std::stringstream ss;
    ss<<'('<<exp1<<'-'<<exp2<<')';
    temp=ss.str();
    return temp;
  }

};
class TimesExpression :public CalculationExpression{
 public:
  TimesExpression(Expression *lhs, Expression *rhs):CalculationExpression(lhs,rhs){}
  virtual long evaluate() const{
    return i1*i2;
  }
  virtual std::string toString() const{
    std::string temp;
    std::stringstream ss;
    ss<<'('<<exp1<<'*'<<exp2<<')';
    temp=ss.str();
    return temp;
  }

};

class DivExpression :public CalculationExpression{
 public:
  DivExpression(Expression *lhs, Expression *rhs):CalculationExpression(lhs,rhs){}
   virtual long evaluate() const{
    return i1/i2;
  }
  virtual std::string toString() const{
    std::string temp;
    std::stringstream ss;
    ss<<'('<<exp1<<'/'<<exp2<<')';
    temp=ss.str();
    return temp;
  }

};
class PlusExpression:public CalculationExpression{
 public:
 PlusExpression(Expression *lhs, Expression *rhs):CalculationExpression(lhs,rhs){}
  virtual long evaluate() const{
    return i1+i2;
  }
  virtual std::string toString() const{
    std::string temp;
    std::stringstream ss;
    ss<<'('<<exp1<<'+'<<exp2<<')';
    temp=ss.str();
    return temp;
  }

};
