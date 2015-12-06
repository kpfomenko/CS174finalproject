#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

static char* PUBLIC_KEY_BYTES = "a810ae51ace032a8b8743a9ef0baa51d";

char * encrypt(char *);

int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("Error: No string to encode\n");
        return -1;
    }
    char* encryption = encrypt(argv[1]);
    // convert encrypted void * to string
    printf("%s\n", encryption);

    return 0;
}

char * encrypt(char *plaintextString) {
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_BYTES);
    paillier_plaintext_t* plainText = paillier_plaintext_from_ui(atoi(plaintextString));
    // paillier_plaintext_t* plainText = paillier_plaintext_from_str(plaintextString);
    paillier_ciphertext_t* ciphertext = paillier_create_enc_zero();

    ciphertext = paillier_enc(ciphertext, publicKey, plainText, &paillier_get_rand_devurandom);
    
    // int sizeOfResult = mpz_sizeinbase(ciphertext->c, 10);
    // char* encrypted = (char*)malloc(sizeof(char)*(sizeOfResult + 2));
    char* encrypted = mpz_get_str(NULL, 10, ciphertext->c);

    paillier_freeplaintext(plainText);
    paillier_freeciphertext(ciphertext);
    paillier_freepubkey(publicKey);

    return encrypted;
}
