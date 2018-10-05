///////////////////////////////////////////////////////
//
// This File: list.c
//
///////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <sys/types.h>
#include <dirent.h>
#include <string.h>
#include "list.h"

//Global Variables
const static int BUFFER = 500;
const int uidNum = 8;
char *proc = "/proc/";
char *statusDIR = "/status";

//Stores each pid into a array of integers
int* generateProcessList(){
  DIR *dir;
  struct dirent *file;
  int *processList = (int*) malloc(sizeof(int)*BUFFER);

  //Tests if directory can be opened, error if it can't
  if(NULL == (dir = opendir(proc)) )
  {
    printf("\n Cannot Open Directory\n");
    exit(1);
  }

  int i = 0;
  while ((file = readdir(dir))){
    if(atoi(file->d_name) != 0){
      if(testOwnership(file->d_name) == 1){
        processList[i] = atoi(file->d_name);
        i++;
      }
    }
  }
  return processList;
}

//Scans status files for pid and compares to
//owner's pid. If true return 1, if false 0
int testOwnership(char* processName){
  char buff[BUFFER];
  char fileLocation[BUFFER];
  strcpy(fileLocation, proc);
  strcat(fileLocation, processName);
  strcat(fileLocation, statusDIR);
  FILE *fp;
  fp = fopen(fileLocation, "r");
  if(fp!=NULL){
    for(int i = 0; i<9; i++ ){
      fgets(buff, BUFFER, fp);
      if(i == uidNum){
        fscanf(fp, "%s", buff);
        fscanf(fp, "%s", buff);

        if(atoi(buff) == getuid()){
          return 1;
        }
      }
    }
    fclose(fp);
  }
  return 0;
}
