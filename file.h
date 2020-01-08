#include <stdlib.h>
#include <stddef.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
 #include <sys/stat.h>
 #include <fcntl.h>
 #include <unistd.h>

/*
*   Fonction permettant de retourner le texte contenu dans un fichier
*   - name : nom du fichier ou chemin d'accès
*/
uint8_t* get_text_from_file(char* name);

/*
*   Fonction permettant de retourner le nombre de caratères dans le fichier donné en paramètre
*   - name : nom du fichier ou chemin d'accès
*/
int file_size(char* name);
