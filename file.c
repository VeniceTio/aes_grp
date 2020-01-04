#include "file.h"

char* getTextFromFile(char* name){
  FILE* file;
  char* text = "";

  file = fopen(name, "r");

  if(file == NULL){
    printf("This file doesn't exists\n");
    fclose(file);
    exit(-1);
  }

  fscanf(file, "%s", text);

  return text;
}

int fileSize(char* name){
  FILE* file;
  file = fopen(name, "rb");

  fseek(file, 0L, SEEK_END);
  int size = ftell(file);

  fclose(file);
  return size;
}
