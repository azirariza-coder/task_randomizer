#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void) {
  // TO DO :
  // iterate over tasks and then write it to file

  FILE *pFile;
  char *fileName = "./task/task_example.txt";
  char *openMode = "r";
  char *tasks[2] = {"Olahraga\n", "Programming\n"};

  pFile = fopen(fileName, openMode);
  if (pFile == NULL) {
    openMode = "w";
    (void)printf("File doesnt exist\n");
    (void)printf("Creating file...\n");
    pFile = fopen(fileName, openMode);

    if (pFile == NULL) {
      (void)exit(EXIT_FAILURE);
    }
  }

  int c = fgetc(pFile);
  if (c != EOF) {
    (void)printf("File not Empty\n");
    openMode = "a";
    pFile = freopen(fileName, openMode, pFile);

    if (pFile == NULL) {
      (void)exit(EXIT_FAILURE);
    }
  }

  if (strcmp(openMode,"r") == 0) {
    (void)printf("Change open mode to write only\n");
    openMode = "w";
    pFile = freopen(fileName, openMode, pFile);

    if (pFile == NULL) {
      (void)exit(EXIT_FAILURE);
    }
  }

  int writeFile = fputs(tasks[0],pFile);
  if (writeFile == EOF){
    (void)exit(EXIT_FAILURE);
  }else{
    (void)printf("Write success!\n");
  }


  fclose(pFile);
  return 0;
}
