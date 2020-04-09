#include "myShell.h"

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

#include <algorithm>
#include <cstdlib>
#include <cstring>
#include <fstream>
#include <iostream>
#include <string>
#include <vector>
extern char ** environ;
void myShell::printPrompt() {
  std::string currDir = getenv("PWD");
  std::cout << "ffosh:" << currDir << "$";
}
std::string readLine() {
  std::string line;
  std::getline(std::cin, line);
  return line;
}

bool myShell::getArgv(std::string & line) {
  //this variable is used to check if is in the two " "
  //status 0 means not in the two " ",1 means in the two " "
  int status = 0;
  //find qutoes
  std::string temp;
  for (unsigned i = 0; i < line.size(); i++) {
    if (line[i] == '"') {
      line.erase(i, 1);
      //when go outside the quotation you should check if temp is empty if not  push_back temp
      if (status == 1) {
        if (!temp.empty()) {
          argvPara.push_back(temp);
          temp.clear();
        }
      }
      //when going inside if temp is not empty, you should push temp to the vector, because quotation will seperate the argument
      if (status == 0) {
        if (!temp.empty()) {
          argvPara.push_back(temp);
          temp.clear();
        }
      }
      status = 1 - status;
    }
    //when in the two qutoes
    if (status == 1) {
      if (line[i] == '"') {
        status = 0;
        if (!temp.empty()) {
          argvPara.push_back(temp);
          temp.clear();
        }
        continue;
      }
      if (line[i] == '\\' && (line[i + 1] == '\\' || line[i + 1] == '"')) {
        line.erase(i, 1);
      }
      //push next element in the temp and execute next loop, this is because I already remove the \ so no matter what is neext element, they should always be put into the temp.
      temp += line[i];
    }

    //when in the two quotation
    if (status == 0) {
      if (line[i] == '"') {
        status = 1;
        if (!temp.empty()) {
          argvPara.push_back(temp);
          temp.clear();
        }
        continue;
      }
      if (line[i] == '\\') {
        line.erase(i, 1);
      }
      //when outside the qutoes
      if (i != line.size() && line[i] != ' ') {
        temp += line[i];
      }
      if (line[i] == ' ' && !temp.empty()) {
        argvPara.push_back(temp);
        temp.clear();
      }
    }
  }
  if (!temp.empty()) {
    argvPara.push_back(temp);
    temp.clear();
  }
  if (status != 0) {
    std::cerr << "Please have an unclosed quotation" << std::endl;
  }
  return status;
}

char ** myShell::vectorToArray() {
  int vectorSize = argvPara.size();
  //generate a char pointer array to store the parameter size equal to size of argvpara vector plus 1
  char ** argv = new char *[vectorSize + 1]();
  //this int used for record the index of array
  int index = 0;
  for (std::vector<std::string>::iterator it = argvPara.begin(); it != argvPara.end(); it++) {
    //for each element in the array allocate space for them;
    argv[index] = new char[(*it).size() + 1];
    argv[index] = strncpy(argv[index], (*it).c_str(), (*it).size() + 1);
    index++;
  }
  //execve need the last one should be NULL
  argv[index] = NULL;
  return argv;
}
void myShell::arrayDelete(char ** array) {
  for (unsigned i = 0; i < (argvPara.size() + 1); i++) {
    delete[] array[i];
  }
  delete[] array;
}
void myShell::getEnvir() {
  //this temp variable is used to store each path in the ECE551PATH
  std::string temp;
  for (unsigned i = 0; i < ECE551PATH.size(); i++) {
    //check if it is ":"
    if (ECE551PATH[i] != ':') {
      //if not ":" add to the temp
      temp += ECE551PATH[i];
    }
    else {
      envirPara.push_back(temp);
      temp.clear();
    }
  }
  //check if temp is empty and if not add to it
  if (!temp.empty()) {
    envirPara.push_back(temp);
    temp.clear();
  }
}
bool myShell::searchCommand(std::string & command) {
  //found is used to record if it has command
  bool found = false;
  //check if it contain /
  if (command.find('/') != std::string::npos) {
    //we can use ifstream to check if it is a valid
    std::ifstream ifs(command.c_str());
    if (ifs.good()) {
      found = true;
    }
  }
  //if command is not full path
  else {
    //check each environment to see whelther it contain command
    for (unsigned i = 0; i < envirPara.size(); i++) {
      std::string fullpath = envirPara[i] + '/' + command;
      //use ifstream to check if it is a valid command
      std::ifstream ifs(fullpath.c_str());
      if (ifs.good()) {
        found = true;
        //change the command to the full path
        command = fullpath;
      }
    }
  }
  return found;
}
void myShell::changeDir() {
  //check if this command is a cd command if not do noting
  if (argvPara[0] == "cd") {
    if (argvPara.size() != 2) {
      std::cerr << "Command is not correct" << std::endl;
    }
    if (argvPara.size() == 2) {
      if (argvPara[1] == "~") {
        if (chdir(getenv("HOME")) != 0) {
          std::cerr << "Change directory failure" << std::endl;
        }
      }
      //if command has two parameter then change the directory
      else {
        if (chdir(argvPara[1].c_str()) != 0) {
          //check if change dir success
          std::cerr << "Change directory failor" << std::endl;
        }
      }
      char cwd[1000];
      getcwd(cwd, 1000);
      //set PWD to currDir to make sure
      if (setenv("PWD", cwd, 1)) {
        std::cerr << "set OLDPWD error" << std::endl;
      }
    }
  }
}
bool myShell::checkVar() {
  bool valid = true;
  //if command argument number smaller than 2 then it is not valid
  if (argvPara.size() < 3) {
    valid = false;
    return valid;
  }
  //I check the var if it is a legal format after I get the argument
  std::string temp = argvPara[1];
  for (unsigned i = 0; i < temp.size(); i++) {
    //check if var is valid
    if ((temp[i] != '_') && (isalnum(temp[i]) == 0)) {
      valid = false;
      return valid;
    }
  }
  return valid;
}
void myShell::exportVar() {
  if (argvPara.size() != 2) {
    std::cerr << "Not legal format for export"
              << "\n";
    return;
  }
  std::string temp = argvPara[1];
  //if format is correct then set it into environment
  if (setenv(temp.c_str(), vars[temp].c_str(), 1) != 0) {
    std::cerr << "Set environment failure" << std::endl;
  }
  //if the user is changing the ECE551PATH, I need to change my path
  if (temp.compare("ECE551PATH") == 0) {
    ECE551PATH = vars[temp];
  }
  Environment = environ;
}
void myShell::setVar(std::string & line) {
  if (checkVar()) {
    std::string temp;
    //this is used for store the argument parameters
    unsigned i = 0;
    //this is a signal to find the second parameter
    unsigned sig = 0;
    for (i = 0; i < line.size(); i++) {
      if (i == 0 && line[i] != ' ') {
        ++sig;
      }
      if (i > 0 && line[i] != ' ' && line[i - 1] == ' ') {
        ++sig;
      }
      //this means when the signal equals to 3 then add all the remaining charater to it
      if (sig >= 3) {
        temp += line[i];
      }
    }
    vars[argvPara[1]] = temp;
  }
  else {
    std::cerr << "Variable format is illegal" << std::endl;
  }
}

//spiltstring function is used for split the string with $
void spiltString(std::string string, std::vector<std::string> & vec) {
  char deli = '$';
  //prev used to record which position is in, pos record the position $
  size_t prev = 0;
  size_t curr = 0;
  std::string token;
  while (curr < string.size() && prev < string.size()) {
    //find the first $ after prev
    curr = string.find(deli, prev);
    if (curr == std::string::npos) {
      curr = string.size();
    }
    std::string token = string.substr(prev, curr - prev);
    if (!token.empty()) {
      vec.push_back(token);
    }
    //update the prev with curr
    prev = curr + 1;
  }
}
void myShell::findVar() {
  for (unsigned i = 0; i < argvPara.size(); i++) {
    if ((argvPara[i].find('$') != std::string::npos)) {
      std::vector<std::string> line;
      spiltString(argvPara[i], line);
      std::string token;
      for (unsigned j = 0; j < line.size(); j++) {
        //store the each line vector element
        std::string lineTemp = line[j];
        //store the variable
        std::string temp;
        for (unsigned p = 0; p < lineTemp.size(); p++) {
          if (lineTemp[p] == '_' || (isalnum(lineTemp[p]) != 0)) {
            temp += lineTemp[p];
          }
          else {
            if (!temp.empty()) {
              std::map<std::string, std::string>::iterator it = vars.find(temp);
              if (it != vars.end()) {
                temp = it->second;
                temp += lineTemp.substr(p, std::string::npos);
                line[j] = temp;
                temp.clear();
                break;
              }
            }
            //else do nothing such as $_
          }
        }
        //check if temp is empty if not find that
        if (!temp.empty()) {
          std::map<std::string, std::string>::iterator it = vars.find(temp);
          if (it != vars.end()) {
            temp = it->second;
            line[j] = temp;
            temp.clear();
          }
        }
      }
      for (unsigned j = 0; j < line.size(); j++) {
        token += line[j];
      }
      argvPara[i] = token;
    }
  }
}

void myShell::revVar() {
  if (argvPara.size() != 2) {
    std::cerr << "Please enter correct nums of parameter"
              << "\n";
  }
  for (std::map<std::string, std::string>::iterator it = vars.begin(); it != vars.end(); ++it) {
    if ((it->first) == argvPara[1]) {
      std::reverse((it->second).begin(), (it->second).end());
      return;
    }
  }
  std::cerr << "There is no such variable" << std::endl;
}

void myShell::launch(std::string & line) {
  pid_t pid, wpid;
  int status;
  char ** argvFinal;
  //search command
  if (searchCommand(argvPara[0]) == false) {
    std::cerr << argvPara[0] << " not found" << std::endl;
    return;
  }
  //convert the vector to array
  argvFinal = vectorToArray();

  pid = fork();
  if (pid == 0) {
    //child process
    if (execve(argvFinal[0], argvFinal, Environment) == -1) {
      arrayDelete(argvFinal);
      std::cerr << "Execute Error" << std::endl;
      exit(EXIT_FAILURE);  //need exit to exit the shell
    }
  }
  else if (pid < 0) {
    //Error forking
    std::cerr << "Forking Error" << std::endl;
  }
  else {
    //parent process
    do {
      wpid = waitpid(pid, &status, WUNTRACED);
      if (wpid == -1) {
        std::cerr << "waitpid" << std::endl;
        exit(EXIT_FAILURE);
      }
      if (WIFEXITED(status)) {
        if (WEXITSTATUS(status)) {
          std::cout << "Program failed with code " << WEXITSTATUS(status) << std::endl;
        }
        else {
          std::cout << "Program was successful" << std::endl;
        }
      }
      else if (WIFSIGNALED(status)) {
        std::cerr << "Terminated by signal " << WTERMSIG(status) << std::endl;
      }
    } while (!WIFEXITED(status) && !WIFSIGNALED(status));
  }
  arrayDelete(argvFinal);
}
//execute function is used to run the shell
void myShell::execute() {
  std::string line;
  while (true) {
    //obtain the current directory and print the prompt
    printPrompt();
    //read the line from the user
    std::string line = readLine();
    //next step I will change the line so I store the line for set function to parse
    std::string lineSet = line;
    //get the current environment
    getEnvir();
    //initialize the argcpara in myshell
    if (getArgv(line) != 0) {
      //I need to clear the argv before leave
      clearArgv();
      continue;
    }
    //if no input then step next
    if (argvPara.size() == 0) {
      continue;
    }
    //replace the command with variable
    findVar();
    //check if command is exit or EOF
    if (line == "exit") {
      exit(EXIT_FAILURE);
    }
    //check if command is cd
    else if (argvPara[0] == "cd") {
      changeDir();
    }
    //check if command is set
    else if (argvPara[0] == "set") {
      setVar(lineSet);
    }
    //check if command is export
    else if (argvPara[0] == "export") {
      exportVar();
    }
    //check if command is rev
    else if (argvPara[0] == "rev") {
      revVar();
    }
    else {
      launch(line);
    }
    //clear the argv vector
    clearArgv();
  }
}

int main(int argc, char * argv[], char * envp[]) {
  //
  myShell shell(environ);
  shell.execute();
  return EXIT_SUCCESS;
}
