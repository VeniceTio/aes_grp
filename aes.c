#include "aes.h"

void keyExpansion()
{

}

void addRoundKey()
{

}

// Chiffrement d'un message
uint8_t* subBytes(uint8_t* message) {
  uint8_t* res = malloc(sizeof(uint8_t)*16);
  for(int i = 0; i < 16; i++) {
    res[i] = subByte(message[i]);
  }
  return res;
}

// Retourne une valeur du tableau sbox
uint8_t subByte(uint8_t val) {
  return sbox[val];
}


uint8_t* shiftRows(uint8_t* message)
{
  // chaque ligne est inversée
   int decalage = 0; // le décalage augmente de 1 a chaque tour de boucle (0 à 3)
   uint8_t* res = malloc(sizeof(uint8_t)*16);
   for(int i = 0; i < 16; i+=4) { // Pour changer de ligne, on incrémente de 4
     res[i] = message[i+(decalage%4)];
     res[i+1] = message[i+(decalage+1)%4];
     res[i+2] = message[i+(decalage+2)%4];
     res[i+3] = message[i+(decalage+3)%4];
     decalage++;
   }
   return res;
}

uint8_t* mixColumns(uint8_t* message)
{
    uint8_t* res = malloc(sizeof(uint8_t)*16);
    uint8_t inter[4][1];
    uint8_t* inter2
    for(int i=0;i<4;i++){
        inter[0][0] = message[i];
        inter[1][0] = message[i+4];
        inter[2][0] = message[i+8];
        inter[3][0] = message[i+12];
        inter2 = multiplyMatrice(inter,matriceMix);
        res[i] = inter2[0];
        res[4+i] = inter2[1];
        res[8+i] = inter2[2];
        res[12+i] = inter2[3];
    }
    return res;
}
