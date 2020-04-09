#include <cstdio>
#include <cstdlib>
#include <iostream>

#include "bstmap.h"

int main(void) {
  BstMap<int, int> map;
  map.add(60, 1);
  map.add(19, 2);
  map.add(93, 3);
  map.add(4, 4);
  map.add(25, 5);
  map.add(84, 6);
  map.add(1, 7);
  map.add(11, 8);
  map.add(21, 9);
  map.add(35, 10);
  map.add(70, 11);
  map.add(86, 12);
  map.add(28,3);
  map.add(29,2);
  map.add(27,5);
  map.inorder();
  std::cout << "\n";
  int ans1 = map.lookup(60);
  int ans2 = map.lookup(35);
  map.remove(27);
  /*  map.remove(29);
  map.remove(70);
  map.remove(35);
  map.remove(21);
  */
  map.inorder();
  std::cout << "\n";
  std::cout << "ans1 should be 1 and =" << ans1 << "\n";
  std::cout << "ans2 should be 10 and =" << ans2 << "\n";

  BstMap<int, int> map2 = map;
  /*map2.remove(25);
  map2.remove(29);
  map2.remove(21);
  */  
std::cout<<"shuchula";
  map2.inorder();
  std::cout << "\n";
  BstMap<int, int> map3(map);
  map3.remove(70);
  map3.remove(28);
  map3.remove(84);
  std::cout<<"map3 shuchu";
  map3.inorder();
  return EXIT_SUCCESS;
  BstMap<int,int> map4;
  for(int i=0;i<10;i++){
    map4.add(i,i+2);
  }
  map4.inorder();

  BstMap<int, int> m1;
  m1.add(3, 0);
  m1.add(9, 1);
  m1.add(2, 2);
  m1.add(6, 3);
  m1.remove(3);
}
