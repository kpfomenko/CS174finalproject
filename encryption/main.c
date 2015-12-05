#include <stdio.h>
#include <stdlib.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

static const int KEY_LENGTH = 128;
static const int ENCRYPTION_BYTE_LENGTH = 65536; // 2^16
static char *const PRIVATE_KEY_BYTES = "54085728d6701953899d4a01bd31d69e";
static char*PUBLIC_KEY_HEX = "a810ae51ace032a8b8743a9ef0baa51d";

void createKeys();
void * encrypt(char *);
char* decrypt(void*);


// TODO: Remove this code from master branch so it is not on AWS

int main(int argc, char* argv[]) {
    void* encryption = encrypt("Avocado");
    printf("encryption: %x\n", (unsigned int) encryption);

    char* decryption = decrypt(encryption);
    printf("decryption: %s\n", decryption);

    return 0;
}



void * encrypt(char *plaintextString) {
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_plaintext_t* plainText = paillier_plaintext_from_str(plaintextString);
    paillier_ciphertext_t* ciphertext = NULL;

    ciphertext = paillier_enc(ciphertext, publicKey, plainText, &paillier_get_rand_devurandom);
    void* ciphertextString = paillier_ciphertext_to_bytes(ENCRYPTION_BYTE_LENGTH, ciphertext);

    paillier_freeplaintext(plainText);
    paillier_freeciphertext(ciphertext);
    paillier_freepubkey(publicKey);

    return ciphertextString;
}

char* decrypt(void* cipherTextBytes) {
    paillier_ciphertext_t* ciphertext = paillier_ciphertext_from_bytes(cipherTextBytes, ENCRYPTION_BYTE_LENGTH);
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_prvkey_t* privateKey = paillier_prvkey_from_hex(PRIVATE_KEY_BYTES, publicKey);

    paillier_plaintext_t* decryptedText = NULL;
    decryptedText = paillier_dec(decryptedText, publicKey, privateKey, ciphertext);
    char* decryptedTextString = paillier_plaintext_to_str(decryptedText);

    paillier_freeciphertext(ciphertext);
    paillier_freepubkey(publicKey);
    paillier_freeprvkey(privateKey);

    return  decryptedTextString;
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
