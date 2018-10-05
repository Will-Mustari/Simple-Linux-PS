///////////////////////////////////////////////////////
//
// This File: options.c
//
///////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include "options.h"

//Global variables
const int ON = 1;
const int OFF = 0;
const int ERROR = -1;
const int maxPid = 32768;

//Initializes all of the options then sets them according to command line input
int initOptions(int argc, char *argv[], struct options *flags){
  flags->p = OFF;
  flags->s = OFF;
  flags->U = ON;
  flags->S = OFF;
  flags->v = OFF;
  flags->c = ON;
  return argsCheck(argc, argv, flags);
}

//argsCheck uses getopt to check the command line arguments and stores them
//into the passed structure. Returns -1 on error.
int argsCheck(int argc, char *argv[], struct options *flags){
  int opt;
  //opterr disables error outputs
  //all cases check for bad inputs and a trailing '-'
  //if trailing '-' is present, disables the option.
  opterr = 0;
  while((opt = getopt(argc, argv, "p:s::U::S::v::c::")) != -1) {
    switch(opt){
      case 's':
        flags->s = ON;
        if(optarg != 0 && argv[optind-1][2] == '-')
          flags->s = OFF;
        else if(optarg != 0)
          return ERROR;
        break;
	//p case is only exception. checks for valid PID argument.
      case 'p':
	if(optarg == NULL){}
	else{
	  flags->p = atoi(optarg);
          if(flags->p <= 0 || flags->p > maxPid)
            return ERROR;
	}
        break;
      case 'U':
        flags->U = ON;
        if(optarg != 0 && argv[optind-1][2] == '-')
          flags->U = OFF;
        else if(optarg != 0)
          return ERROR;
        break;
      case 'S':
        flags->S = ON;
        if(optarg != 0 && argv[optind-1][2] == '-')
          flags->S = OFF;
        else if(optarg != 0)
          return ERROR;
        break;
      case 'v':
        flags->v = ON;
        if(optarg != 0 && argv[optind-1][2] == '-')
          flags->v = OFF;
        else if(optarg != 0)
          return ERROR;
        break;
      case 'c':
        flags->c = ON;
        if(optarg != 0 && argv[optind-1][2] == '-')
          flags->c = OFF;
        else if(optarg != 0)
          return ERROR;
        break;
	//'?' case is a catch-all for unnacceptable arguments
      case '?':
        return ERROR;
    }
  }
  //returns 0 if everything passed 
  return 0;
}
