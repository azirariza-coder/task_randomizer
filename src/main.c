#include <stdio.h>
#include <string.h>

void fRead(FILE *);

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
    (void)ungetc(c, pFile);
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
      (void)printf("Write Failed\n");
      return 5;
    }
  }
  (void)fRead(pFile);

  (void)printf("Closing file...\n");
  int closeStatus = fclose(pFile);
  if (closeStatus == EOF) {
    (void)printf("Read failed!\n");
    return 6;
  }

  return 0;
}

void fRead(FILE *pFile) {

  char buffer[2][20];
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
}
