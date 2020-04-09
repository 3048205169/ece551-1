#include "election.h"

#include <stdio.h>
#include <stdlib.h>
//include any other headers you need here...

state_t parseLine(const char * line) {
  //STEP 1: write me
  int i = 0;
  state_t t;
  if (line == NULL) {
    printf("Please enter something!");
    exit(EXIT_FAILURE);
  }
  for (; line[i] != ':'; i++) {
    if (i > MAX_STATE_NAME_LENGTH - 1 || line[i] == '\0') {
      printf("StateName has something wrong!");
      exit(EXIT_FAILURE);
    }
    t.name[i] = line[i];
  }
  t.name[i] = '\0';
  i++;
  t.population = 0;
  t.electoralVotes = 0;
  if (line[i] == ':') {
    printf("Format Wrong");
    exit(EXIT_FAILURE);
  }
  for (; line[i] != ':'; i++) {
    if (line[i] == '\0' || line[i] - '0' > 9 || line[i] - '0' < 0) {
      printf("population has something wrong!");
      exit(EXIT_FAILURE);
    }
    else {
      t.population = (10 * t.population + (line[i] - '0'));
    }
  }
  i++;
  if (line[i] == ':') {
    printf("Format Wrong");
    exit(EXIT_FAILURE);
  }
  for (; line[i] != '\0'; i++) {
    if (line[i] == ':' || line[i] - '0' > 9 || line[i] - '0' < 0 || line[i] == '\0') {
      printf("votes has something wrong!!");
      exit(EXIT_FAILURE);
    }
    t.electoralVotes = (10 * t.electoralVotes + (line[i] - '0'));
  }
  return t;
}

unsigned int countElectoralVotes(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 2: write me
  unsigned int num = 0;
  for (size_t i = 0; i < nStates; i++) {
    if (2 * voteCounts[i] > stateData[i].population) {
      num = num + stateData[i].electoralVotes;
    }
  }
  return num;
}

void printRecounts(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 3: write me
  for (size_t i = 0; i < nStates; i++) {
    double num = 1.0 * voteCounts[i] / stateData[i].population;
    if (num < 0.505 && num > 0.495) {
      printf("%s requires a recount (Candidate A has %.2f%% of the vote)\n",
             stateData[i].name,
             100.0 * num);
    }
  }
}

void printLargestWin(state_t * stateData, uint64_t * voteCounts, size_t nStates) {
  //STEP 4: write me
  size_t num = 0;
  for (size_t i = 1; i < nStates; i++) {
    if ((1.0 * voteCounts[i] / stateData[i].population) >
        1.0 * voteCounts[num] / stateData[num].population) {
      num = i;
    }
  }
  printf("Candidate A won %s with %.2f%% of the vote\n",
         stateData[num].name,
         100.0 * voteCounts[num] / stateData[num].population);
}
