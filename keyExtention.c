#include "keyExtention.h"
#include "aes.h"

//***********************************************************
//Algorithme d'extention de clef: genere X clefs pour X Rounds
void keyExtention(uint8_t key[KEY_LENGTH / 8], uint8_t* extKeyW[(KEY_LENGTH / 32) * (NB_ROUNDS+1)]) {
    //Copier la clef dans le extKey et le transformer en Mots de Bytes
    for(int i = 0; i < 3; ++i) {
        uint8_t word[4] = { key[i * 4], key[i * 4 + 1], key[i * 4 + 2], key[i * 4 + 3]};
        memcpy ( word, extKeyW[i], strlen(word));
    }

    //uint8_t temp[4];
    //memcpy ( key, extKey, strlen(key) );
}

//***********************************************************
//Shift les Bytes du mot d'un cran vers la gauche
void rotWord(uint8_t* word) {
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

char* stringToHexStr(char* text, char output[256]) {

  int len = strlen(text);

  // Convert text to hex.
  for (int i = 0, j = 0; i < len; ++i, j += 2)
    sprintf(output + j, "%02x", text[i] & 0xff);

    int i2 = (strlen(output) / 2);
    int i1 = (KEY_LENGTH / 8);


  //Add zeros in order to match the key size
  if(i1 > i2) {
    int diff = (KEY_LENGTH / 8) - (strlen(output) / 2);
    char* hexZero = "00";

    for(int i = 0; i < diff; ++i) {
        strcat(output, hexZero );
    }
  }

  return output;
}

void hexStrToKey(char* hex, uint8_t* key) {

    //Le nombre de Bits Hexadecimaux doit etre egal au nombre de bits de la Clef
    for(int i = 0; i < KEY_LENGTH/8; i++)
    {
        //Le sub string prends la valeur du bit hexadecimal qui nous interesse (par tranche de 2 chiffres)
        char substr[3];

        //Copier dans le sub string
        strncpy(substr, hex+(i*2), 2);
        substr[2] = '\0';

        //Convertir en int pour stocker dans la clef key[16]
        key[i] = (uint8_t)strtol(substr, NULL, 16);
    }
}
