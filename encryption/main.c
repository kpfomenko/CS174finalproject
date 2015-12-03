#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

int main(int argc, char* argv[]) {
    printf("Hello World\n");

    paillier_pubkey_t* publicKey = (paillier_pubkey_t*) malloc(sizeof(paillier_pubkey_t));
    paillier_prvkey_t* privateKey = (paillier_prvkey_t*) malloc(sizeof(paillier_prvkey_t));

    paillier_keygen(128, &publicKey, &privateKey, &paillier_get_rand_devurandom);

    paillier_ciphertext_t* ciphertext = paillier_create_enc_zero();
    paillier_plaintext_t* plainText = paillier_plaintext_from_str("Avocado");

    paillier_enc(ciphertext, publicKey, plainText, &paillier_get_rand_devurandom);

    printf("public key %s\n", paillier_pubkey_to_hex(publicKey));
    printf("private key %s\n", paillier_prvkey_to_hex(privateKey));
    printf("plainText: %s\n", paillier_plaintext_to_str(plainText));

    paillier_plaintext_t*decryptedText = NULL;
    decryptedText = paillier_dec(decryptedText, publicKey, privateKey, ciphertext);
    printf("decrypted text: %s\n", paillier_plaintext_to_str(decryptedText));


    paillier_freepubkey(publicKey);
    paillier_freeprvkey(privateKey);
    paillier_freeciphertext(ciphertext);
    paillier_freeplaintext(plainText);
    paillier_freeplaintext(decryptedText);

    return 0;
}