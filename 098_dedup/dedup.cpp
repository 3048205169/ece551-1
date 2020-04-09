#include <sstream>
#include<string.h>
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <unordered_map>
#include <sys/stat.h>
#include <sys/types.h>
#include <cstdio>

#include <dirent.h>
//open file
std::string fileReader(const char *dire){
  std::ifstream ifs_in(dire);
  std::string line;
  std::string key="";
  while(ifs_in>>line){
    key=key+line;
  }
  return key;
}
//mode check
mode_t  modeCheck(const char *dire){
  struct stat sb;
  //check available  
  if(lstat(dire,&sb)==-1){
    std::cerr<<"lstat"<<std::endl;
    exit(EXIT_FAILURE);
  }
  return sb.st_mode&S_IFMT;
}
//function to remove duplication
void dedup(const char * dire,std::unordered_map<size_t,std::string> &map){
  DIR *dir;
  struct dirent *thisFile;
  //opendirectory
  //std::cout << dire << "\n";
  dir=opendir(dire);
  if(dir==NULL){
    std::cerr << "cannot open directory"
              << "\n";
    exit(EXIT_FAILURE);
  }
  else{
    while((thisFile=readdir(dir))!=NULL){
      std::string dirStr(dire);
      std::string filename(thisFile->d_name);
      if(dirStr.length() > 0 && dirStr[dirStr.length() - 1] != '/') {
        dirStr = dirStr + '/';
      }
      std::string fullname=dirStr+filename;
      mode_t mode=modeCheck(fullname.c_str());
      //diretory
      if(mode == S_IFDIR){
	//enter the directory and do that again
	//std::cout << "directory: " << fullname << "\n";
	if(strcmp(thisFile->d_name,".")==0||strcmp(thisFile->d_name,"..")==0){
	  continue;
	}
	else{
	  dedup(fullname.c_str(),map);
	}
      }
      //file is regular file
      else if(mode == S_IFREG){
	
	std::string content=fileReader(fullname.c_str());
	//	std::cout<<"zhelide content"<<content<<"\n";
	std::hash<std::string> myhash;
	size_t key=myhash(content);
	std::unordered_map<size_t, std::string>::const_iterator it = map.find(key);
	//duplication
	if (it != map.end()) {
	  std::cout << "#Removing " << fullname << " (duplicate of " << it->second << ")."
		    << std::endl;
	  std::cout << "rm " << fullname << std::endl;
	}
	else {
	  map.insert(std::pair<size_t, std::string>(key, fullname));
	}
	
	//std::cout<< "regular file: " <<fullname<<"\n";
      }
    }
  }
  closedir(dir);
 }

int main(int argc, char ** argv){
  //construct a hash map to store value
  std::unordered_map<size_t,std::string> map;
  if(argc==1){
    std::cerr<<"at least 1 input"<<std::endl;
    return EXIT_FAILURE;
  }
  else{
    //print shell
    std::cout << "#!/bin/bash"
              << "\n";
    for(int i=1;i<argc;i++){
      dedup(argv[i],map);
    }
  }
  return EXIT_SUCCESS;
}
