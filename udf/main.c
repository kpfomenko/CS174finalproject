//
// Created by Deanna Hartsook on 11/29/15.
//

#include <stdio.h>
#include <gmp.h>
#include <ctype.h>
#include "sum.h"
#include "../libpaillier-0.8/paillier.h"

static char* PUBLIC_KEY_HEX = "a810ae51ace032a8b8743a9ef0baa51d";
static char *const PRIVATE_KEY_BYTES = "54085728d6701953899d4a01bd31d69e";

int main(int argc, char* argv[]) {
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_prvkey_t* privateKey = paillier_prvkey_from_hex(PRIVATE_KEY_BYTES, publicKey);

    paillier_plaintext_t* plaintext10 = paillier_plaintext_from_str("5");
    paillier_plaintext_t* plaintext5 = paillier_plaintext_from_str("10");

    paillier_ciphertext_t* ciphertext10 = NULL;
    paillier_ciphertext_t* ciphertext5 = NULL;

    ciphertext10 = paillier_enc(ciphertext10, publicKey, plaintext10, &paillier_get_rand_devurandom);
    ciphertext5 = paillier_enc(ciphertext5, publicKey, plaintext5, &paillier_get_rand_devurandom);

    paillier_ciphertext_t* result15 = paillier_create_enc_zero();
    paillier_mul(publicKey, result15, ciphertext10, ciphertext5);

    paillier_plaintext_t* result15Plain = NULL;
    result15Plain = paillier_dec(result15Plain, publicKey, privateKey, result15);
    char* result15String = paillier_plaintext_to_str(result15Plain);

    printf("result15Plain = %s\n\n", result15String);
    int i;
    for (i = 0; i < strlen(result15String); i++) {
        printf("char: %c\n", result15String[i]);
        if (isdigit(result15String[i])) {
            printf("%d", result15String[i]);
            printf("decimal: %d\n",result15String[i]);
        } else {
            printf("%d",result15String[i] - 96);
            printf("decimal: %d\n",result15String[i] - 96);
        }
        printf("decimal: %d\n",result15String[i] - 96);
    }

    printf("\n");


//    char* cipherString1 = "23309940613470805178272794585130224459147464893744862436128788211776205037989"; // 10
//    char* cipherString2 = "45919584308665688553301034068930257149172101699752143257332880523710415216216"; // 5
//
//    paillier_ciphertext_t* ciphertext1 = paillier_create_enc_zero() ;
//    mpz_init_set_str(ciphertext1, cipherString1, 10);
//
//    int sizeOfResult = mpz_sizeinbase(ciphertext1, 10) + 2;
//    char* newCipherText1 = (char*)malloc(sizeof(char)*sizeOfResult);
//    mpz_get_str(newCipherText1, 10, ciphertext1);
//    printf("first ciphertext was %s\n", newCipherText1);
//
//    paillier_ciphertext_t* ciphertext2 = paillier_create_enc_zero() ;
//    mpz_init_set_str(ciphertext2, cipherString2, 10);
//
//    sizeOfResult = mpz_sizeinbase(ciphertext2,10) + 2;
//    char* newCipherText2 = (char*)malloc(sizeof(char)*sizeOfResult);
//    mpz_get_str(newCipherText2 , 10, ciphertext2);
//    printf("second ciphertext was %s\n", newCipherText2);
//
//    paillier_ciphertext_t* result = paillier_create_enc_zero();
//
//    paillier_mul(publicKey, result, ciphertext1, ciphertext2);
//
//    sizeOfResult = mpz_sizeinbase(result,10) + 2;
//    char* resultString = (char*)malloc(sizeof(char)*sizeOfResult);
//    mpz_get_str(resultString, 10, result);
//
//    printf("result = %s\n", resultString);
//
//    paillier_freeciphertext(ciphertext2);
//    paillier_freepubkey(publicKey);

    return 0;
}