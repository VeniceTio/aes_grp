#include "file.h"

int fileSize(char* name){
  FILE* file;
  file = fopen(name, "r");

  fseek(file, 0L, SEEK_END);
  int size = ftell(file);

  fclose(file);
  return size;
}

uint8_t* getTextFromFile(char* name){
  FILE* file = NULL;
  uint8_t* text = malloc(sizeof(uint8_t) * fileSize(name));

  if((file = fopen(name, "r")) == NULL){
    printf("This file doesn't exists\n");
    fclose(file);
    exit(-1);
  }

  fscanf(file, "%s", text);

  return text;
}
