#include "utils.h"
#include "math.h"
#include <stdio.h>
#include <stdlib.h>

/*
 * Fonction permettant de réaliser un shift sur monône
 * - monône : le monôme sur lequel on doit effectuer le shift
 */
uint8_t shift_monome(uint8_t monome) {
    uint8_t verif = 128; // 1000 0000
    if((verif & monome) != 0) {
        uint8_t a8 = 27; // 0001 1011
        return a8;
    } else {
        return monome << 1;
    }
}

/*
 * Fonction permettant de réaliser la multiplication a*(P)
 * - polynome : le polynôme sur lequel on doit réaliser la multiplication
 */
uint8_t shift_polynome(uint8_t polynome) {
    uint8_t res = 0; // 0000 0000
    for(size_t i = 0; i < 8; i++) {
        uint8_t verif = (1 << i); // 0000 0001 << i
        if((verif & polynome) != 0) {
            res = res^shift_monome(verif);
        }
    }
    return res;
}

/*
 * Fonction permettant de shift un polynome k fois
 * - k : le nombre de fois qu'on doit shift le polynome
 * - polynome : le polynome sur lequel on doit effectuer le shift
 */
uint8_t shift_n_polynome(int k, uint8_t polynome) {
    uint8_t res = polynome;
    for(size_t i = 0; i < k; i++) {
        res = shift_polynome(res);
    }
    return res;
}

/*
 * Fonction permettant d'appliquer un OU exclusif entre 2 mots de 4 bytes
 * - word1 : le premier mot
 * - word2 : le deuxième mot
 */
uint8_t* xor_words(uint8_t* word1, uint8_t* word2) {
    static uint8_t* res;
    res = malloc(sizeof(uint8_t) * 4);

    res[0] = word1[0] ^ word2[0];
    res[1] = word1[1] ^ word2[1];
    res[2] = word1[2] ^ word2[2];
    res[3] = word1[3] ^ word2[3];

    return res;
}

/*
 * Fonction permettant de réaliser la multiplication entre deux octets
 * - o1 : le premier octet permettant la multiplication
 * - o2 : le deuxième octet permettant la multiplication
 */
uint8_t multiplication(uint8_t o1, uint8_t o2) {
    uint8_t res = 0; // 0000 0000
    for(int i = 0; i < 8; i++) {
        uint8_t verif = 1 << i; //0000 0001 << i
        if((o1 & verif) != 0) {
            res = res^shift_n_polynome(i,o2);
        }
    }
    return res;
}


/*
 * Fonction permettant d'extraire les 2 chiffres du bit en représentation héxadécimale
 * - byte : le byte dans lequel on doit extraire les deux chiffres
 */
struct HexDigits get_hex_digits(uint8_t byte) {
    struct HexDigits digits;
    digits.d1 = (int)floor(byte / 16); //Extrait le premier chiffre
    digits.d2 = byte % 16; //Extrait le deuxième chiffre

    return digits;
}

/*
 * Fonction permettant d'afficher un mot de 4 bytes
 * - word : le mot à afficher
 */
void print_word(uint8_t* word) {
    printf("[%i, %i, %i, %i]\n", word[0], word[1], word[2], word[3]);
}

/*
 * Fonction permettant de d'afficher un mot de 4 bytes en hexadécimal
 * - word : le mot à afficher
 */
void print_word_hex(uint8_t* word) {
    printf("[%x, %x, %x, %x]\n", word[0] & 0xff, word[1] & 0xff, word[2] & 0xff, word[3] & 0xff);
}

/*
 * Fonction permettant d'afficher les uint de façon plus graphique
 * - display : les uint à afficher
 */
void print(uint8_t* display){
    for(size_t i = 0; i < 16; i+=4)
    {
        printf("[%x, %x, %x, %x]\n", display[i] & 0xff, display[i+1] & 0xff, display[i+2] & 0xff, display[i+3] & 0xff);
    }
}

/*
 * Fonction permettant d'afficher les uint de façon plus graphique
 * - display : les uint à afficher
 */
void print_ver(uint8_t* display){
    for(size_t i = 0; i < 4; i++)
    {
        printf("[%x, %x, %x, %x]\n", display[i] & 0xff, display[i+4] & 0xff, display[i+8] & 0xff, display[i+12] & 0xff);
    }
}



