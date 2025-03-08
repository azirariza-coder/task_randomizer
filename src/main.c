#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>


void fRead(FILE *);

int main(void) {

  (void)printf("Is the file exist yet?, create file if not\n");

  FILE *pFile;
  char *fileName = "./task/task_example.txt";
  char *openMode = "r";
  const char *tasks[3] = {"Olahraga\n", "Programming\n","Gaming\n"};

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
    (void)ungetc(c, pFile);
    (void)printf("File not Empty\n");
    (void)fRead(pFile);
    (void)printf("Closing file...\n");
    int closeStatus = fclose(pFile);
    if (closeStatus == EOF) {
      (void)printf("Close failed\n");
      return 2;
    }
    return 0;
  }

  (void)ungetc(c, pFile);

  (void)printf("Beyond here file empty, start write!!\n");

  if (strcmp(openMode, "w") != 0) {
    (void)printf("Change open mode to write only\n");
    openMode = "w";
    pFile = freopen(fileName, openMode, pFile);

    if (pFile == NULL) {
      (void)printf("Write Failed\n");
      return 3;
    }
  }

  for (size_t i = 0; i < (sizeof(tasks) / sizeof(tasks[0])); i++) {

    int writeFile = fputs(tasks[i], pFile);

    if (writeFile == EOF) {
      (void)printf("Write failed!\n");
      return 4;
    }
  }
  (void)printf("Write success!\n");

  if (strcmp(openMode, "r") != 0) {
    openMode = "r";
    pFile = freopen(fileName, openMode, pFile);
    if (pFile == NULL) {
      (void)printf("Read Failed\n");
      return 5;
    }
  }

  (void)printf("Read Success\n");
  (void)fRead(pFile);
  

  (void)printf("Closing file...\n");
  int closeStatus = fclose(pFile);
  if (closeStatus == EOF) {
    (void)printf("Close failed!\n");
    return 6;
  }

  return 0;
}

void fRead(FILE *pFile) {

  char buffer[3][20];
  int c = 0;
  size_t j = 0;

  for (size_t i = 0; i < sizeof(buffer)/ sizeof(buffer[0]); i++) {
    j = 0;
    while ((c = fgetc(pFile)) != '\n'){
      buffer[i][j] = c;
      j++;
    }
    buffer[i][j] = '\0';
  }

  for (size_t i = 0; i < sizeof(buffer)/ sizeof(buffer[0]); i++) {
  (void)printf("%s\n", buffer[i]);
  }


  time_t  result = time(NULL);
  (void) srand(result);
  (void)printf("Hasil randomize : %s\n",buffer[rand()% 3]);

}


