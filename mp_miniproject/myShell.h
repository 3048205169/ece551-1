#ifndef __MYSHELL_H__
#define __MYSHELL_H__
#include <stdlib.h>

#include <iostream>
#include <map>
#include <string>
#include <vector>
class myShell
{
 private:
  //currDir which is used to save the system directory
  std::string currDir;
  //argvParmeter is used to save user's input line
  std::vector<std::string> argvPara;
  //ECE551PATH
  std::string ECE551PATH;
  //envir is used to store the environment variable which is actually ECE551PATH but seperate them into elements
  std::vector<std::string> envirPara;
  //vars is used to record var pairs
  std::map<std::string, std::string> vars;
  //environment variables
  char ** Environment;

 public:
  //getCurrDir which is used to obtain the current directory
  /*std::string getCurrDir(){ 
			currDir=getcwd(NULL,0);
			return currDir;
		}*/
  // constructor
  myShell(char ** environ) {
    Environment = environ;
    currDir = getenv("PWD");
    ECE551PATH = getenv("PATH");
  }
  //printPrompt function is used to print the prompt
  void printPrompt();
  //execute is used for the whole framework of the command shell
  void execute();
  // launch is used to execute behavior
  void launch(std::string & line);
  //get argvParmeter from the user
  bool getArgv(std::string & line);
  //get pointer array for excve to run
  char ** vectorToArray();
  //delete array
  void arrayDelete(char **);
  //clearArgv is use to clear argv vector so that my shell can get new command from user
  void clearArgv() {
    argvPara.clear();
    envirPara.clear();
    //note vars do not need to be cleared
  }
  //getEnvir is used to set the environmental path for myshell
  void getEnvir();
  //search command
  bool searchCommand(std::string & line);
  //changedirectory is used to change the directory
  void changeDir();
  //setVar function is used for store the variable
  void setVar(std::string & line);
  //findvar is used to check if command include the variable in the vars map and replace them
  void findVar();
  //check if var is valid format
  bool checkVar();
  //export the variable into evironment
  void exportVar();
  //reverse the var
  void revVar();
};

#endif
