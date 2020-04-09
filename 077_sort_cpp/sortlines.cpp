#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <vector>

void sortString(std::istream &f){
  std::vector<std::string> data;
  std::string line;
  while(getline(f,line)){
    data.push_back(line);
  }
  
  if (!f.eof() && !f) {
    std::cerr << "Something wrong about reading the file.\n";
    exit(EXIT_FAILURE);
  }
  
  std::sort(data.begin(),data.end());
  std::vector<std::string>::iterator it = data.begin();
  while(it !=data.end()){
    std::cout << *it << "\n";
    ++it;
  }
}

int main (int argc, char **argv){
  if(argc==1){
    sortString(std::cin);
  }
  else{
    for(int i=1;i<argc;i++){
      std::ifstream ifs(argv[i]);
      if(ifs.is_open()){
	sortString(ifs);
      }
      else{
	std::cerr<<"open file fail.\n";
	exit(EXIT_FAILURE);
      }
    }
  }
}
