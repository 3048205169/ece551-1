#include <stdlib.h>
#include <stdio.h>

struct _retire_info{
  int months;
  double contribution;
  double rate_of_return;
};
typedef struct _retire_info retire_info;
double compute (int startAge, double initial, retire_info retired){
  for(int i=1;i<=retired.months;i++){
    int	age = startAge/12;
    int	month=startAge%12;
    printf("Age %3d month %2d you have $%.2lf\n",age,month,initial);
    initial=initial+(initial*retired.rate_of_return)+retired.contribution;
    startAge++;
  }
  return initial;
}
void retirement(int startAge, double initial, retire_info working, retire_info retired) {
  double balance = initial;
  balance = compute(startAge, balance, working);
  startAge = startAge + working.months;
  balance = compute(startAge, balance, retired);
}
int main(){
  retire_info working;
  working.months=489;
  working.contribution=1000;
  working.rate_of_return=0.045/12;
  retire_info retired;
  retired.months=384;
  retired.contribution=-4000;
  retired.rate_of_return=0.01/12;
  int age =327;
  double initial=21345;
  retirement(age,initial,working,retired);
  return 0;
}
