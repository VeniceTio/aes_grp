#include <stdint.h>
#include <stddef.h>
#include <stdlib.h>

void sub_word(uint8_t word[4]);

uint8_t* sub_bytes(uint8_t* word);
uint8_t sub_byte(uint8_t val);

uint8_t* inv_sub_bytes(uint8_t* word);
uint8_t inv_sub_byte(uint8_t val);

int state_index(int row, int column);
void add_round_key(uint8_t* state, uint8_t key[4][4]);

uint8_t* shift_rows(uint8_t* word);
uint8_t* mix_columns(uint8_t* word);

uint8_t* inv_shift_rows(uint8_t* word);
uint8_t* inv_mix_columns(uint8_t* word);
uint8_t* multiply(uint8_t* column);
uint8_t* inv_multiply(uint8_t* column);
uint8_t* get_column(uint8_t* matrice, int pos);
void copy_vertical(uint8_t* input, uint8_t* output);
void cipher(uint8_t in[16], uint8_t out[16], uint8_t** extKey);
void inv_cipher(uint8_t in[16], uint8_t out[16],uint8_t** extKey);

#ifndef GLOBALVAR_AES
#define GLOBALVAR_AES

extern int KEY_LENGTH;
extern int NB_ROUNDS;

uint8_t sbox[256];

extern const uint8_t inv_sbox[256];

extern const uint8_t matrice_mix[16];

extern const uint8_t inv_matrice_mix[16];

#endif
