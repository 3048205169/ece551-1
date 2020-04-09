#include <cstdlib>
#include <cstdio>
#include <iostream>

int main() {
  int * a = new int(4);
  delete a;
  * a = 3;
  std::cout << *a << std::endl;
  return 1;
}
