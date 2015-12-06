//
// Created by Deanna Hartsook on 11/29/15.
//

#include <stdio.h>
#include <gmp.h>
#include "sum.h"
#include "../libpaillier-0.8/paillier.h"

static char* PUBLIC_KEY_HEX = "a810ae51ace032a8b8743a9ef0baa51d";

int main(int argc, char* argv[]) {
    char* cipherString1 = "328ddd0f1dcd333f86d3bf073aff492ebbe8809333f64b228e2d8c3dbb4f5c6f";
    char* cipherString2 = "30aa46c351204bb59be4aafe1a5e45ab0bcb9044a7a41482c3f210c09c1538f4";

    paillier_ciphertext_t* ciphertext1 = paillier_create_enc_zero() ;
    mpz_init_set_str(ciphertext1, cipherString1, 10);
//
//    int sizeOfResult = mpz_sizeinbase(ciphertext1, 16) + 2;
//    char* newCipherText1 = (char*)malloc(sizeof(char)*sizeOfResult);
//    mpz_get_str(newCipherText1 , 16, cipherString1);
//    printf("first ciphertext was %s\n", newCipherText1);

    paillier_ciphertext_t* ciphertext2 = paillier_create_enc_zero() ;
    mpz_init_set_str(ciphertext2, cipherString2, 10);

//    sizeOfResult = mpz_sizeinbase(ciphertext2,16) + 2;
//    char* newCipherText2 = (char*)malloc(sizeof(char)*sizeOfResult);
//    mpz_get_str(newCipherText2 , 16, cipherString2);
//    printf("second ciphertext was %s\n", newCipherText2);

    paillier_ciphertext_t* result = paillier_create_enc_zero();
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_mul(publicKey, result, ciphertext1, ciphertext2);

    int sizeOfResult = mpz_sizeinbase(result,10) + 2;
    char* resultString = (char*)malloc(sizeof(char)*sizeOfResult);
    mpz_get_str(resultString, 16, result);

    printf("result = %s\n", resultString);

    paillier_freeciphertext(ciphertext2);
    paillier_freepubkey(publicKey);

    return 0;
}