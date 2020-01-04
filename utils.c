#include "utils.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

//***********************************************************
// Applique le OU exclusif entre 2 Mots de 4 Bytes
uint8_t* xorWords(uint8_t* word1, uint8_t* word2) {
    static uint8_t* res;
    res = malloc(sizeof(uint8_t) * 4);

    res[0] = word1[0] ^ word2[0];
    res[1] = word1[1] ^ word2[1];
    res[2] = word1[2] ^ word2[2];
    res[3] = word1[3] ^ word2[3];

    return res;
}

//***********************************************************
//Un overload de print pour afficher un Mot de 4 Bytes en Hexadicimal
void printWordHex(uint8_t* word) {
    printf("[%x, %x, %x, %x]\n", word[0] & 0xff, word[1] & 0xff, word[2] & 0xff, word[3] & 0xff);
}

//***********************************************************
//Un overload de print pour afficher un Mot de 4 Bytes
void printWord(uint8_t* word) {
    printf("[%i, %i, %i, %i]\n", word[0], word[1], word[2], word[3]);
}

//***********************************************************
//Un overload de print pour afficher les uint de facon plus graphique
void printVer(uint8_t* display){
    for(size_t i = 0; i < 4; i++)
    {
        printf("[%x, %x, %x, %x]\n", display[i] & 0xff, display[i+4] & 0xff, display[i+8] & 0xff, display[i+12] & 0xff);
    }
}

//***********************************************************
//Un overload de print pour afficher les uint de facon plus graphique
void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%x, %x, %x, %x]\n", display[i] & 0xff, display[i+1] & 0xff, display[i+2] & 0xff, display[i+3] & 0xff);
    }
}

//***********************************************************
//Extrait les 2 chiffres du bit en representation Hexadecimale
struct HexDigits getHexDigits(uint8_t byte) {
    struct HexDigits digits;
    //Extrait le premier chiffre
    digits.d1 = (int)floor(byte / 16);
    //Extrait le deuxieme chiffre
    digits.d2 = byte % 16;

    return digits;
}
uint8_t shiftMonome(uint8_t monome) {
    // réalise un shit de 1 sur un monome
    uint8_t verif = 128; // 1000 0000
    if((verif & monome) != 0) {
        uint8_t a8 = 27; // 0001 1011
        return a8;
    } else {
        return monome << 1;
    }
}

uint8_t shiftPolynome(uint8_t polynome) {
    // Réalise la multiplication a*(P)
    uint8_t res = 0; // 0000 0000
    for(int i = 0; i < 8; i++) {
        uint8_t verif = (1 << i); // 0000 0001 << i
        if((verif & polynome) != 0) {
            res = res^shiftMonome(verif);
        }
    }
    return res;
}

uint8_t shiftNPolynome(int k, uint8_t polynome) {
    uint8_t res = polynome;
    for(int i = 0; i < k; i++) {
        res = shiftPolynome(res);
    }
    return res;
}

uint8_t multiplication(uint8_t o1, uint8_t o2) {
    // Réalise la multiplication entre deux octets
    uint8_t res = 0; // 0000 0000
    for(int i = 0; i < 8; i++) {
        uint8_t verif = 1 << i; //0000 0001 << i
        if((o1 & verif) != 0) {
            res = res^shiftNPolynome(i,o2);
        }
    }
    return res;
}

