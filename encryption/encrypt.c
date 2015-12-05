#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

static const int ENCRYPTION_BYTE_LENGTH = 128;
static char* PUBLIC_KEY_BYTES = "a810ae51ace032a8b8743a9ef0baa51d";

void * encrypt(char *);

int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("Error: No string to encode\n");
    }
    //void * encryption ==> array of bytes
    unsigned char* encryption = (unsigned char *) encrypt(argv[1]);
    //convert to hexidecimal
    int i;
    for (i = 0; i < ENCRYPTION_BYTE_LENGTH; i++){
        if (i > 0) printf(":");
        printf("%02X", encryption[i]);
    }
    printf("\n");
    return 0;
}

void * encrypt(char *plaintextString) {
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_BYTES);
    paillier_plaintext_t* plainText = paillier_plaintext_from_str(plaintextString);
    paillier_ciphertext_t* ciphertext = NULL;

    ciphertext = paillier_enc(ciphertext, publicKey, plainText, &paillier_get_rand_devurandom);
    void* ciphertextString = paillier_ciphertext_to_bytes(ENCRYPTION_BYTE_LENGTH, ciphertext);

    paillier_freeplaintext(plainText);
    paillier_freeciphertext(ciphertext);
    paillier_freepubkey(publicKey);

    return ciphertextString;
}
