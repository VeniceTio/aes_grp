#include "keyExpansion.h"
#include "aes.h"
#include "utils.h"

uint8_t rCon[] = { 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1B, 0x36 };

/*
 * Fonction permettant de récupérer une clé
 * - keyNum : le numéro de la clé
 * - extKey : la clé étendu
 */
uint8_t* get_key(int keyNum, uint8_t* extKey) {
    uint8_t* key = malloc(sizeof(uint8_t) * 4);

    key[0] = extKey[keyNum * 4];
    key[1] = extKey[(keyNum * 4) + 1];
    key[2] = extKey[(keyNum * 4) + 2];
    key[3] = extKey[(keyNum * 4) + 3];

    return key;
}

/*
 * Fonction permettant de générer un mot de 4 bytes à partir du tableau de rCon
 * - i : index
 */
uint8_t* get_r_con_word(int i) {
    static uint8_t rConWord[4];

    rConWord[0] = rCon[i-1];
    rConWord[1] = 0;
    rConWord[2] = 0;
    rConWord[3] = 0;

    return rConWord;
}

/*
 * Méthode permettant de générer une clef a 16 byte en se basant sur une phrase
 * - text : le texte entré
 * - output : la clef
 */
void str_to_key_byte(char* text, uint8_t output[16]) {
  int len = strlen(text);

  // Convertir Char en uint8_t (byte)
  for (size_t i = 0; i < len; ++i)
    output[i] = (uint8_t)text[i];

  int i2 = len;
  int i1 = (KEY_LENGTH / 8);

  //Ajout de zéros dans le but d'atteindre la taille de la clé
  if(i1 > i2) {
    int diff = i1 - i2;

    for(size_t i = diff; i < (KEY_LENGTH / 8); ++i) {
        output[i] = 0;
    }
  }
}

/*
 * Algorithme d'extention de clef: génére X+1 clefs pour X Rounds
 * Applique le chiffrement sur le premier mot de la clef. Ensuite, le chiffrement se propage
 * car le Deuxieme mot = (Premier mot) XOR (Deuxieme mot de la clef precedente)
 * ETC jusqu'a NB_CLEFS = NB_ROUNDS + 1
 * - key : la clé
 * - extKeyW : la clé étendu
 */
void key_expansion(uint8_t key[KEY_LENGTH / 8], uint8_t** extKeyW) {
    int keyWords = (KEY_LENGTH / 32); // 4 pour la clef de 128 bits

    // Copier la clef dans le extKey et le transformer en Mots de Bytes
    for(size_t i = 0; i < (KEY_LENGTH / 32); i++) {
        uint8_t word[4] = { key[i * 4], key[i * 4 + 1], key[i * 4 + 2], key[i * 4 + 3]};
        memcpy (&extKeyW[i], word, sizeof(uint8_t) * 4);

        //print_word(word);
    }

    // Boucle d'extention de clef
    for(size_t i = 4; i < 4 * (NB_ROUNDS+1); ++i) {
        // Cree le mot temp = le mot precedent
        uint8_t* temp = malloc(sizeof(uint8_t) * 4);
        memcpy (temp, &extKeyW[i-1], sizeof(uint8_t) * 4);

        // Si c'est le premier mot de la clef
        if(i % keyWords == 0) {
            // Appliquer la rotation, substitution, rCon
            rot_word(temp);
            sub_word(temp);
            uint8_t* rCon = get_r_con_word(i/keyWords);
            temp = xor_words(temp, rCon );
        }
        // ...
        else if(keyWords > 6 && (i % keyWords) == 4) {
            sub_word(temp);
        }

        //Xor le mot (de la meme position) de la clef precedente avec le mot temp
        uint8_t* newWord = malloc(sizeof(uint8_t) * 4);
        memcpy (newWord, &extKeyW[i-keyWords], sizeof(uint8_t) * 4);
        newWord = xor_words(newWord, temp);

        //Le nouveau mot dans la clef est newWord
        memcpy (&extKeyW[i], newWord, sizeof(uint8_t) * 4);
    }
    //printf("\n");
}


/*
 * Fonction permettant de shifter les bytes du mot d'un cran vers la gauche
 * - word : le mot qui contient les bytes qu'on doit shifter
 */
void rot_word(uint8_t* word) {
    uint8_t temp = word[0];
    word[0] = word[1];
    word[1] = word[2];
    word[2] = word[3];
    word[3] = temp;
}

/*
 * Fonction permettant de transformer un string en hexadécimale
 * - text : le texte qu'on doit transformer
 */
char* string_to_hex_str(char* text, char output[256]) {

  int len = strlen(text);

  // Convert text to hex.
  for (size_t i = 0, j = 0; i < len; ++i, j += 2)
    sprintf(output + j, "%02x", text[i] & 0xff);

  int i2 = (strlen(output) / 2);
  int i1 = (KEY_LENGTH / 8);


  //Add zeros in order to match the key size
  if(i1 > i2) {
    int diff = (KEY_LENGTH / 8) - (strlen(output) / 2);
    char* hexZero = "00";

    for(size_t i = 0; i < diff; ++i) {
        strcat(output, hexZero );
    }
  }

  return output;
}

/*
 * Méthode permettant de transformer un hexadécimale en clé
 *  - hex : l'hexadécimale
 *  - key : la clé
 */
void hex_str_to_key(char* hex, uint8_t* key) {

    //Le nombre de Bits Hexadecimaux doit etre egal au nombre de bits de la Clef
    for(size_t i = 0; i < KEY_LENGTH/8; i++)
    {
        //Le sub string prends la valeur du bit hexadecimal qui nous interesse (par tranche de 2 chiffres)
        char substr[3];

        //Copier dans le sub string
        strncpy(substr, hex+(i*2), 2);
        substr[2] = '\0';

        //Convertir en int pour stocker dans la clef key[16]
        uint8_t keyBit = (uint8_t)strtol(substr, NULL, 16);

        key[i] = keyBit;
    }
}
