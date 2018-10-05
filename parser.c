///////////////////////////////////////////////////////
//
// This File: parser.c
//
///////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "parser.h"

//Global Variables
static const int BUFFER = 255;
static const int numFields = 15;
static const int stateField = 3;
static const int userField = 14;
static const int sysField = 15;
char *procDIR = "/proc/";
char *statDIR = "/stat";
char *statmDIR = "/statm";
char *cmdlineDIR = "/cmdline";

//Allocates memory for the process info and prints the output
int generatePrint(struct options *flags, int processID){
  struct info* pInfo = (struct info*) malloc(sizeof(struct info));
  initInfo(pInfo, processID);

  printf("Process %s: ", pInfo->pid);
  if(flags->s == ON && pInfo->state != '0')
    printf("%c ", pInfo->state); 
  if(flags->U == ON && pInfo->userTime != NULL)
    printf("utime=%s ", pInfo->userTime);
  if(flags->S == ON && pInfo->systemTime != NULL)
    printf("stime=%s ", pInfo->systemTime);
  if(flags->v == ON && pInfo->vm != NULL)
    printf("vmemory=%s ", pInfo->vm);
  if(flags->c == ON && pInfo->cmdline != NULL)
    printf("[%s]", pInfo->cmdline);
  printf("\n");
  
  free(pInfo);
  return 0;
}

//Stores the process ID and calls the next three functions
void initInfo(struct info *pInfo, int processID){
  char pidStr[BUFFER];
  sprintf(pidStr, "%d", processID);
  pInfo->pid = pidStr;

  pInfo->state = '0';
  pInfo->userTime = NULL;
  pInfo->systemTime = NULL;
  pInfo->vm = NULL;
  pInfo->cmdline = NULL;
  
  parseStat(pInfo);
  parseStatm(pInfo);
  parseCmdline(pInfo);
}

//Parses /proc/<pid>/stat and stores the current state, 
//user time, and system time
void parseStat(struct info *pInfo){
  char buff[BUFFER];
  char fileLocation[BUFFER];
  char *p;
  strcpy(fileLocation, procDIR);
  strcat(fileLocation, pInfo->pid);
  strcat(fileLocation, statDIR);
  FILE *fp;
  fp = fopen(fileLocation, "r");
  int i = 0;
  if (fp!=NULL){
    while(i < numFields){
      i++; //at i of each field it stores corresponding value. 
      fscanf(fp, "%s", buff);
      if(i == stateField)
        pInfo->state = buff[0];
      if(i == userField) {
	p = (char*)malloc(sizeof(buff));
        strcpy(p, buff);
	pInfo->userTime = p;
	p = NULL;
      }
      if(i == sysField) {
	p = (char*)malloc(sizeof(buff));
        strcpy(p, buff);
	pInfo->systemTime = p;
	p = NULL;
      }
    }
    fclose (fp);
  }
}

//Parses /proc/<pid>/statm and stores the amount of
//virtual memory used
void parseStatm(struct info *pInfo){
  char buff[BUFFER];
  char fileLocation[BUFFER];
  char *p;
  strcpy(fileLocation, procDIR);
  strcat(fileLocation, pInfo->pid);
  strcat(fileLocation, statmDIR);
  FILE *fp;
  fp = fopen(fileLocation, "r");
  if(fp!=NULL){
    p = (char*)malloc(sizeof(buff));
    fscanf(fp, "%s", buff);
    strcpy(p, buff); //vm is first value in file
    pInfo->vm = p;
    p = NULL;
    fclose(fp);
  }
}

//Parses the command line and stores the entire 
//command for a given pid
void parseCmdline(struct info *pInfo){
  char buff[BUFFER];
  char fileLocation[BUFFER];
  char *p;
  strcpy(fileLocation, procDIR);
  strcat(fileLocation, pInfo->pid);
  strcat(fileLocation, cmdlineDIR);
  FILE *fp;
  fp = fopen(fileLocation, "r");
  if(fp!=NULL){
    p = (char*)malloc(sizeof(buff));
    fgets(buff, sizeof buff, fp);
    strcpy(p, buff); //if it's larger than buff, then that section is truncated.
    pInfo->cmdline = p;
    p = NULL;
    fclose(fp);
  }
}
