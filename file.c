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
  uint8_t* text = malloc(sizeof(uint8_t) * fileSize(name));

  int fd = open(name, 0);

  if(fd != -1)
    read(fd, text, fileSize(name));

  return text;
}
