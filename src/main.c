#include <stdio.h>
#include <string.h>

int main(void) {
  // TO DO :
  // iterate over tasks and then write it to file
  
  (void)printf("Is the file exist yet?, create file if not\n");

  FILE *pFile;
  char *fileName = "./task/task_example.txt";
  char *openMode = "r";
  const char *tasks[2] = {"Olahraga\n", "Programming\n"};

  pFile = fopen(fileName, openMode);

  if (pFile == NULL) {
    openMode = "w";
    (void)printf("File doesnt exist\n");
    (void)printf("Creating file...\n");
    pFile = fopen(fileName, openMode);

    if (pFile == NULL) {
      (void)printf("Write failed\n");
      return 1;
    }
  }

  (void)printf("Beyond here file already exist, but is it empty?\n");

  int c = fgetc(pFile);

  if (c != EOF) {
    (void)printf("File not Empty\n");
    (void)printf("Closing file...\n");
    int closeStatus = fclose(pFile);
    if (closeStatus == EOF) {
      (void)printf("Close failed\n");
      return 2;
    }
    return 0;
  }

  (void)printf("Beyond here file empty, start write!!\n");

  if (strcmp(openMode, "r") == 0) {
    (void)printf("Change open mode to write only\n");
    openMode = "w";
    pFile = freopen(fileName, openMode, pFile);

    if (pFile == NULL) {
      (void)printf("Write Failed\n");
      return 3;
    }
  }

  for (size_t i = 0; i < (sizeof(tasks)/sizeof(tasks[0]) ); i++) {

    int writeFile = fputs(tasks[i], pFile);

    if (writeFile == EOF) {
      (void)printf("Write failed!\n");
      return 4;
    } 
  }
  (void)printf("Write success!\n");

  (void)printf("Closing file...\n");
  int closeStatus = fclose(pFile);
  if (closeStatus == EOF) {
    (void)printf("Read failed!\n");
    return 5;
  }
  return 0;
}
