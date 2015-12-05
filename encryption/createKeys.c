#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

static const int KEY_LENGTH = 128;

void createKeys();

int main(int argc, char* argv[]) {
    createKeys();
    return 0;
}

void createKeys() {
    paillier_pubkey_t* publicKey = (paillier_pubkey_t*) malloc(sizeof(paillier_pubkey_t));
    paillier_prvkey_t* privateKey = (paillier_prvkey_t*) malloc(sizeof(paillier_prvkey_t));

    paillier_keygen(KEY_LENGTH, &publicKey, &privateKey, &paillier_get_rand_devurandom);

    char* publicKeyHex = paillier_pubkey_to_hex(publicKey);
    char* privateKeyHex = paillier_prvkey_to_hex(privateKey);

    printf("public key: %s\n", publicKeyHex);
    printf("private key: %s\n", privateKeyHex);

    paillier_freepubkey(publicKey);
    paillier_freeprvkey(privateKey);
}
