#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

int main(int argc, char* argv[]) {
    printf("Hello World\n");

    paillier_pubkey_t* publicKey = (paillier_pubkey_t*) malloc(sizeof(paillier_pubkey_t));
    paillier_prvkey_t* privateKey = (paillier_prvkey_t*) malloc(sizeof(paillier_prvkey_t));

    paillier_keygen(128, &publicKey, &privateKey, &paillier_get_rand_devurandom);

    printf("public key %s\n", paillier_pubkey_to_hex(publicKey));
    printf("private key %s\n", paillier_prvkey_to_hex(privateKey));
    return 0;
}