#include "aes.h"

void keyExpansion()
{

}

void addRoundKey()
{

}

void subBytes(int posX, int posY)
{

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

void mixColumns()
{

}
