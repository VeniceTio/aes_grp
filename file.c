#include "file.h"

/*
*   Retourne le nombre de caratères dans le fichier donné en paramètre
*   - name : nom du fichier ou chemin d'accès
*/
int file_size(char* name){
  FILE* file;
  file = fopen(name, "r");

  fseek(file, 0L, SEEK_END);
  int size = ftell(file);

  fclose(file);
  return size;
}

/*
*   Retourne le texte contenu dans un fichier
*   - name : nom du fichier ou chemin d'accès
*/
uint8_t* get_text_from_file(char* name){
  uint8_t* text = malloc(sizeof(uint8_t) * file_size(name));

  int fd = open(name, 0);

  if(fd != -1)
    read(fd, text, file_size(name));

  return text;
}
