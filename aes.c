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

// Chiffrement d'un message
uint8_t* invSubBytes(uint8_t* message) {
  uint8_t* res = malloc(sizeof(uint8_t)*16);
  for(int i = 0; i < 16; i++) {
    res[i] = invSubByte(message[i]);
  }
  return res;
}

// Retourne une valeur du tableau sbox
uint8_t invSubByte(uint8_t val) {
  return inv_sbox[val];
}

uint8_t* shiftRows(uint8_t* message)
{
  // chaque ligne est inversée
   int shift = 0; // le décalage augmente de 1 a chaque tour de boucle (0 à 3)
   uint8_t* res = malloc(sizeof(uint8_t)*16);
   for(int i = 0; i < 16; i+=4) { // Pour changer de ligne, on incrémente de 4
     res[i] = message[i+(shift%4)];
     res[i+1] = message[i+(shift+1)%4];
     res[i+2] = message[i+(shift+2)%4];
     res[i+3] = message[i+(shift+3)%4];
     shift++;
   }
   return res;
}

uint8_t* mixColumns(uint8_t* message)
{
    uint8_t* res = malloc(sizeof(uint8_t)*16);
    uint8_t* inter = malloc(sizeof(uint8_t)*4);
    uint8_t* inter2 = malloc(sizeof(uint8_t)*4);
    for(int i=0;i<4;i++){
        inter[0] = message[i];
        inter[1] = message[i+4];
        inter[2] = message[i+8];
        inter[3] = message[i+12];
        printf("envoyé : \n[%c]\n[%c]\n[%c]\n[%c]\n",inter[0], inter[1],inter[2],inter[3]);
        inter2 = multiplyMatrice(inter,4,1,matriceMix,4,4);
        res[i] = inter2[0];
        res[4+i] = inter2[1];
        res[8+i] = inter2[2];
        res[12+i] = inter2[3];
    }
    return res;
}
