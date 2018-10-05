///////////////////////////////////////////////////////
//
// This File: main.c
//
///////////////////////////////////////////////////////

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include "options.h"
#include "list.h"
#include "parser.h"

//Driver class. Ties the three other .c files together. Responsible for passing
//values between the classes.
int main(int argc, char *argv[]){
  //declares flags, then initializes them using options.c
  struct options* flags = (struct options*) malloc(sizeof(struct options));
  int *processes;

  if(initOptions(argc, argv, flags) == -1){
      printf("%s\n", "Incorrect usage");
      exit(EXIT_FAILURE);
  }

  //if p is not selected, uses list.c to create a list of pid
  //then outputs information for them according to flags
  if(flags->p == 0){
      processes = generateProcessList();
      int i = 0;
      while (processes[i] != 0){
          generatePrint(flags, processes[i]);
          i++;
    }
    exit(EXIT_SUCCESS);  
  }
  //otherwise it prints the information for the single pid. Also
  //tests if given pid is a valid input.
  else{ 
      processes = generateProcessList();
      int i = 0;
      int printed = 0;
      while (processes[i] != 0){
	if(processes[i] == flags->p){
            generatePrint(flags, flags->p);
	    printed = 1;
	}
	i++;
      }
      if(printed == 0){
	 printf("PID DOES NOT EXIST\n");
         exit(EXIT_FAILURE);
      }
      exit(EXIT_SUCCESS);
  } 
}
