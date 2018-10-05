///////////////////////////////////////////////////////
//
// This File: parser.h
//
///////////////////////////////////////////////////////]

#ifndef PARSER_H   /* Include guard */
#define PARSER_H

#include "options.h"

char *procDIR;
char *statDIR;
char *statmDIR;

//Structure containing all of the information that can be
//associated with a process
//All array of characters except for state with is a single character
struct info{
  char* pid;
  char* userTime; 
  char* systemTime;
  char* vm;
  char* cmdline;
  char state;
};

//calls initInfo then prints the information
int generatePrint(struct options *flags, int processID);

//calls three helpers functions after setting pid value
void initInfo(struct info *pInfo, int processID);

//responsible for parsing the stat file
//sets usertime, systemtime, and state
void parseStat(struct info *pInfo);

//responsible for parsing the statm file
//sets the vm
void parseStatm(struct info *pInfo);

//responsible for parsing the cmdline file
//sets the cmdline info
void parseCmdline(struct info *pInfo);

#endif
