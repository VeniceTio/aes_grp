#include <stddef.h>
#include <stdlib.h>
#include <string.h>

#include "aes.h"
#include "utils.h"
#include "keyExpansion.h"

int KEY_LENGTH = 128;
int NB_ROUNDS = 10;

uint8_t sbox[256] = {
  //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
  0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76,
  0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0,
  0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15,
  0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75,
  0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84,
  0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf,
  0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8,
  0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2,
  0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73,
  0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb,
  0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79,
  0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08,
  0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a,
  0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e,
  0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf,
  0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16 };

const uint8_t inv_sbox[256] = {
  0x52, 0x09, 0x6a, 0xd5, 0x30, 0x36, 0xa5, 0x38, 0xbf, 0x40, 0xa3, 0x9e, 0x81, 0xf3, 0xd7, 0xfb,
  0x7c, 0xe3, 0x39, 0x82, 0x9b, 0x2f, 0xff, 0x87, 0x34, 0x8e, 0x43, 0x44, 0xc4, 0xde, 0xe9, 0xcb,
  0x54, 0x7b, 0x94, 0x32, 0xa6, 0xc2, 0x23, 0x3d, 0xee, 0x4c, 0x95, 0x0b, 0x42, 0xfa, 0xc3, 0x4e,
  0x08, 0x2e, 0xa1, 0x66, 0x28, 0xd9, 0x24, 0xb2, 0x76, 0x5b, 0xa2, 0x49, 0x6d, 0x8b, 0xd1, 0x25,
  0x72, 0xf8, 0xf6, 0x64, 0x86, 0x68, 0x98, 0x16, 0xd4, 0xa4, 0x5c, 0xcc, 0x5d, 0x65, 0xb6, 0x92,
  0x6c, 0x70, 0x48, 0x50, 0xfd, 0xed, 0xb9, 0xda, 0x5e, 0x15, 0x46, 0x57, 0xa7, 0x8d, 0x9d, 0x84,
  0x90, 0xd8, 0xab, 0x00, 0x8c, 0xbc, 0xd3, 0x0a, 0xf7, 0xe4, 0x58, 0x05, 0xb8, 0xb3, 0x45, 0x06,
  0xd0, 0x2c, 0x1e, 0x8f, 0xca, 0x3f, 0x0f, 0x02, 0xc1, 0xaf, 0xbd, 0x03, 0x01, 0x13, 0x8a, 0x6b,
  0x3a, 0x91, 0x11, 0x41, 0x4f, 0x67, 0xdc, 0xea, 0x97, 0xf2, 0xcf, 0xce, 0xf0, 0xb4, 0xe6, 0x73,
  0x96, 0xac, 0x74, 0x22, 0xe7, 0xad, 0x35, 0x85, 0xe2, 0xf9, 0x37, 0xe8, 0x1c, 0x75, 0xdf, 0x6e,
  0x47, 0xf1, 0x1a, 0x71, 0x1d, 0x29, 0xc5, 0x89, 0x6f, 0xb7, 0x62, 0x0e, 0xaa, 0x18, 0xbe, 0x1b,
  0xfc, 0x56, 0x3e, 0x4b, 0xc6, 0xd2, 0x79, 0x20, 0x9a, 0xdb, 0xc0, 0xfe, 0x78, 0xcd, 0x5a, 0xf4,
  0x1f, 0xdd, 0xa8, 0x33, 0x88, 0x07, 0xc7, 0x31, 0xb1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xec, 0x5f,
  0x60, 0x51, 0x7f, 0xa9, 0x19, 0xb5, 0x4a, 0x0d, 0x2d, 0xe5, 0x7a, 0x9f, 0x93, 0xc9, 0x9c, 0xef,
  0xa0, 0xe0, 0x3b, 0x4d, 0xae, 0x2a, 0xf5, 0xb0, 0xc8, 0xeb, 0xbb, 0x3c, 0x83, 0x53, 0x99, 0x61,
  0x17, 0x2b, 0x04, 0x7e, 0xba, 0x77, 0xd6, 0x26, 0xe1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0c, 0x7d };

const uint8_t matrice_mix[16]={
  0x02, 0x03, 0x01, 0x01,
  0x01, 0x02, 0x03, 0x01,
  0x01, 0x01, 0x02, 0x03,
  0x03, 0x01, 0x01, 0x02
};

const uint8_t inv_matrice_mix[16]={
  0x0E, 0x0B, 0x0D, 0x09,
  0x09, 0x0E, 0x0B, 0x0D,
  0x0D, 0x09, 0x0E, 0x0B,
  0x0B, 0x0D, 0x09, 0x0E
};

/*
*   Fonction permettant d'appliquer la S-box sur un mot de 4 Bytes
*   - word : mot de 4 uint8_t
*/
void sub_word(uint8_t word[4]) {
    for(int i = 0; i < 4; ++i) {
        word[i] = sbox[word[i]];
    }
}

/*
*   Fonction permettant de
*   - state :
*   - key :
*/
void add_round_keyVer(uint8_t* state, uint8_t key[4][4]) {

    for(int i = 0; i < 4; ++i) {
        state[4 * i]   = state[4 * i]   ^ key[i][0];
        state[4 * i+1] = state[4 * i+1] ^ key[i][1];
        state[4 * i+2] = state[4 * i+2] ^ key[i][2];
        state[4 * i+3] = state[4 * i+3] ^ key[i][3];
    }
}

/*
*   Fonction permettant de
*   - state :
*   - key :
*/
void add_round_key(uint8_t* state, uint8_t key[4][4]) {
    for(int i = 0; i < 4; ++i) {
        state[i + 0]   = state[i + 0]   ^ key[i][0];
        state[i + 4] = state[i + 4] ^ key[i][1];
        state[i + 8] = state[i + 8] ^ key[i][2];
        state[i + 12] = state[i + 12] ^ key[i][3];
    }
}

/*
*   Fonction permettant le chiffrement d'une matrice
*   - matrice : la matrice à chiffrer
*/
uint8_t* sub_bytes(uint8_t* matrice) {
  uint8_t* res = malloc(sizeof(uint8_t)*16);
  for(int i = 0; i < 16; i++) {
    res[i] = sub_byte(matrice[i]);
  }
  return res;
}

/*
*   Fonction permettant de retourner une valeur du tableau sbox
*   - val : la valeur cherché dans le tableau
*/
uint8_t sub_byte(uint8_t val) {
  return sbox[val];
}

/*
*   Fonction permettant le déchiffrement d'une matrice
*   - matrice :
*/
uint8_t* inv_sub_bytes(uint8_t* matrice) {
  uint8_t* res = malloc(sizeof(uint8_t)*16);
  for(int i = 0; i < 16; i++) {
    res[i] = inv_sub_byte(matrice[i]);
  }
  return res;
}

/*
*   Fonction permettant de retourner une valeur du tableau inv_sbox
*   - val : la valeur à récupérer
*/
uint8_t inv_sub_byte(uint8_t val) {
  return inv_sbox[val];
}

/*
*   Fonction permettant de retourner la position dans le tableau d'une valeur à partir de ces coordoonées
*   - row : la ligne voulue
*   - column : la colonne voulue
*/
int state_index(int row, int column) {
    return (column * 4 + row);
}

/*
*   Fonction permettant de mélanger les lignes d'une matrice 4*4
*   - matrice : la matrice à mélanger
*/
uint8_t* shift_rows(uint8_t* matrice)
{
   int shift = 0;
   uint8_t* res = malloc(sizeof(uint8_t)*16);
   for(size_t i = 0; i < 4; i++) {
     res[state_index(i, 0)] =  matrice[state_index(i, (shift + 0) % 4)];
     res[state_index(i, 1)] =  matrice[state_index(i, (shift + 1) % 4)];
     res[state_index(i, 2)] =  matrice[state_index(i, (shift + 2) % 4)];
     res[state_index(i, 3)] =  matrice[state_index(i, (shift + 3) % 4)];
     shift++;
   }
   return res;
}

/*
*   Fonction permettant de remettre les lignes d'une matrice 4*4 dans le bon sens
*   - matrice : la matrice devant retourné à son état initial
*/
uint8_t* inv_shift_rows(uint8_t* matrice){
   int shift = 0;
   uint8_t* res = malloc(sizeof(uint8_t)*16);
   for(int i = 0; i < 16; i+=4) {
     res[i] = matrice[i+(shift+4)%4];
     res[i+1] = matrice[i+(shift+5)%4];
     res[i+2] = matrice[i+(shift+6)%4];
     res[i+3] = matrice[i+(shift+7)%4];
     shift--;
   }
   return res;
}

/*
*   Fonction permettant de renvoyer la colonne à la position pos depuis la matrice matrice
*   - matrice : la matrice d'où récupérer une colonne
*   - pos : position de la colonne
*/
uint8_t* get_column(uint8_t* matrice, int pos){
    uint8_t* column = malloc(sizeof(uint8_t)*4);
    for(int i = 0; i < 4; i++) {
        column[i] = matrice[i*4 + pos];
    }
    return column;
}

/*
*   Fonction permettant de renvoyer la ligne à la position pos depuis la matrice matrice
*   - matrice : matrice d'où récupérer une ligne
*   - pos : position de la ligne
*/
uint8_t* getRow(uint8_t* matrice, int pos){
    uint8_t* row = malloc(sizeof(uint8_t)*4);
    for(int i = pos*4; i < (pos*4)+4; i++) {
        row[i%4] = matrice[i];
    }
    return row;
}

/*
*   Fonction permettant de mélanger les colonnes d'une matrice 4*4
*   - matrice : matrice à mélanger
*/
uint8_t* mix_columns(uint8_t* matrice)
{
  uint8_t* new_matrice = malloc(sizeof(uint8_t)*16);
  uint8_t* temp = malloc(sizeof(uint8_t)*4);

  for (size_t i = 0; i < 4; i++) {
    temp = getRow(matrice, i);
    temp = multiply(temp);
    new_matrice[i*4] = temp[0];
    new_matrice[i*4+1] = temp[1];
    new_matrice[i*4+2] = temp[2];
    new_matrice[i*4+3] = temp[3];
  }

  free(temp);
  return new_matrice;
}

/*
*   Fonction permettant de remettre les colonnes d'une matrice 4*4 dans le bon sens
*   - matrice : la matrice devant retourné à son état initial
*/
uint8_t* inv_mix_columns(uint8_t* matrice){
  uint8_t* new_matrice = malloc(sizeof(uint8_t)*16);
  uint8_t* temp = malloc(sizeof(uint8_t)*4);

  for (size_t i = 0; i < 4; i++) {
    temp = get_column(matrice, i);
    temp = inv_multiply(temp);
    new_matrice[i*4] = temp[0];
    new_matrice[i*4+1] = temp[1];
    new_matrice[i*4+2] = temp[2];
    new_matrice[i*4+3] = temp[3];
  }

  uint8_t copy[16];
  copyVertical(new_matrice, copy);

  memcpy(new_matrice, copy, sizeof(uint8_t) * 16);

  free(temp);
  return new_matrice;
}

/*
*   Fonction permettant de multiplier une colonne de matrice par matrice_mix
*   - column : la colonne à multiplier
*/
uint8_t* multiply(uint8_t* column){
  uint8_t* res = malloc(sizeof(uint8_t)*4);

    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
    res[3] = 0;

    for(int i=0;i<4;i++){
        res[0] = res[0] ^ multiplication(column[i],matrice_mix[0+i]);
        res[1] = res[1] ^ multiplication(column[i],matrice_mix[4+i]);
        res[2] = res[2] ^ multiplication(column[i],matrice_mix[8+i]);
        res[3] = res[3] ^ multiplication(column[i],matrice_mix[12+i]);
    }

  return res;
}

/*
*   Fonction permettant de diviser une colonne par inv_matrice_mix
*   - column : la colonne à multiplier
*/
uint8_t* inv_multiply(uint8_t* column){
    uint8_t* res = malloc(sizeof(uint8_t)*4);

    res[0] = 0;
    res[1] = 0;
    res[2] = 0;
    res[3] = 0;

    for(int i=0;i<4;i++){
        res[0] = res[0] ^ multiplication(column[i],inv_matrice_mix[0+i]);
        res[1] = res[1] ^ multiplication(column[i],inv_matrice_mix[4+i]);
        res[2] = res[2] ^ multiplication(column[i],inv_matrice_mix[8+i]);
        res[3] = res[3] ^ multiplication(column[i],inv_matrice_mix[12+i]);
    }

  return res;
}

/*
*   Fonction permettant de chiffré un bloc de 16 octets
*   - in : le bloc à chiffrer
*   - out : le bloc chiffré
*   - extKey : la clé étendue
*/
void cipher(uint8_t in[16], uint8_t out[16], uint8_t** extKey) {
    uint8_t state[16];

    memcpy (state, in, sizeof(uint8_t) * 16);
    uint8_t key[4][4];
    memcpy(&key[0], &extKey[0], sizeof(uint8_t) * 4);
    memcpy(&key[1], &extKey[1], sizeof(uint8_t) * 4);
    memcpy(&key[2], &extKey[2], sizeof(uint8_t) * 4);
    memcpy(&key[3], &extKey[3], sizeof(uint8_t) * 4);

    printf("%i", key[0][0]);

    printf("\nState Init: \n");
    print_ver(state);

    printf("\nKey: \n");
    print_ver(key);


    add_round_keyVer(state, key);
    for(int i = 1; i < NB_ROUNDS; ++i) {
        printf("\nStart of Round: %i\n", i);
        print_ver(state);

        memcpy(state, sub_bytes(state), sizeof(uint8_t) * 16);
        printf("\nAfter sub_bytes: \n");
        print_ver(state);

        memcpy(state, shift_rows(state), sizeof(uint8_t) * 16);
        printf("\nAfter shift_rows: \n");
        print_ver(state);

        memcpy(state, mix_columns(state), sizeof(uint8_t) * 16);
        printf("\nAfter mix_columns: \n");
        print_ver(state);

        memcpy(&key[0], &extKey[(i * 4)+0], sizeof(uint8_t) * 4);
        memcpy(&key[1], &extKey[(i * 4)+1], sizeof(uint8_t) * 4);
        memcpy(&key[2], &extKey[(i * 4)+2], sizeof(uint8_t) * 4);
        memcpy(&key[3], &extKey[(i * 4)+3], sizeof(uint8_t) * 4);

        printf("\nKey: \n");
        print_ver(key);

        add_round_keyVer(state, key);
    }

    printf("ROUND 10");

    memcpy(state, sub_bytes(state), sizeof(uint8_t) * 16);
    printf("\nAfter sub_bytes: \n");
    print_ver(state);

    memcpy(state, shift_rows(state), sizeof(uint8_t) * 16);
    printf("\nAfter shift_rows: \n");
    print_ver(state);

    memcpy(&key[0], &extKey[(NB_ROUNDS) * 4 +0], sizeof(uint8_t) * 4);
    memcpy(&key[1], &extKey[(NB_ROUNDS) * 4 +1], sizeof(uint8_t) * 4);
    memcpy(&key[2], &extKey[(NB_ROUNDS) * 4 +2], sizeof(uint8_t) * 4);
    memcpy(&key[3], &extKey[(NB_ROUNDS) * 4 +3], sizeof(uint8_t) * 4);

    printf("\nKey: \n");
    print_ver(key);

    add_round_keyVer(state, key);
    printf("\nAfter AddKey: \n");
    print_ver(state);

    memcpy (out, state, sizeof(uint8_t) * 16);

    printf("\nOUTPUT: \n");
    print_ver(out);
}

/*
 * Fonction permettant de
 * - input :
 * - output :
 */
void copyVertical(uint8_t* input, uint8_t* output) {
    for(int i = 0; i < 4; ++i) {
        output[0 + i] = input[i * 4 + 0];
        output[4 + i] = input[i * 4 + 1];
        output[8 + i] = input[i * 4 + 2];
        output[12 + i] = input[i * 4 + 3];
    }
}

/*
*   Fonction permettant de déchiffrer un bloc de 16 octets
*   - in : le bloc à déchiffer
*   - out : le bloc déchiffré
*   - extKey : la clé étendue
*/
void inv_cipher(uint8_t in[16], uint8_t out[16],uint8_t** extKey){
    uint8_t state[16];
    uint8_t key[4][4];

    memcpy (state, in, sizeof(uint8_t) * 16);
    copyVertical(in, state);

    memcpy(&key[0], &extKey[(NB_ROUNDS) * 4 +0], sizeof(uint8_t) * 4);
    memcpy(&key[1], &extKey[(NB_ROUNDS) * 4 +1], sizeof(uint8_t) * 4);
    memcpy(&key[2], &extKey[(NB_ROUNDS) * 4 +2], sizeof(uint8_t) * 4);
    memcpy(&key[3], &extKey[(NB_ROUNDS) * 4 +3], sizeof(uint8_t) * 4);

    add_round_key(state, key);

    for(int i = NB_ROUNDS-1; i >0 ; --i) {

        memcpy(state, inv_shift_rows(state), sizeof(uint8_t) * 16);

        memcpy(state, inv_sub_bytes(state), sizeof(uint8_t) * 16);

        memcpy(&key[0], &extKey[(i * 4)+0], sizeof(uint8_t) * 4);
        memcpy(&key[1], &extKey[(i * 4)+1], sizeof(uint8_t) * 4);
        memcpy(&key[2], &extKey[(i * 4)+2], sizeof(uint8_t) * 4);
        memcpy(&key[3], &extKey[(i * 4)+3], sizeof(uint8_t) * 4);

        add_round_key(state, key);

        memcpy(state, inv_mix_columns(state), sizeof(uint8_t) * 16);
    }

    memcpy(state, inv_shift_rows(state), sizeof(uint8_t) * 16);

    memcpy(state, inv_sub_bytes(state), sizeof(uint8_t) * 16);

    memcpy(&key[0], &extKey[0], sizeof(uint8_t) * 4);
    memcpy(&key[1], &extKey[1], sizeof(uint8_t) * 4);
    memcpy(&key[2], &extKey[2], sizeof(uint8_t) * 4);
    memcpy(&key[3], &extKey[3], sizeof(uint8_t) * 4);

    add_round_key(state, key);

    memcpy (out, state, sizeof(uint8_t) * 16);
}
