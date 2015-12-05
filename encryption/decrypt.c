#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

static const int ENCRYPTION_BYTE_LENGTH = 128;
static char *const PRIVATE_KEY_BYTES = "54085728d6701953899d4a01bd31d69e";
static char* PUBLIC_KEY_BYTES = "a810ae51ace032a8b8743a9ef0baa51d";

char* decrypt(char*);

int main(int argc, char* argv[]) {
    if(argc != 2){
        printf("Error: No string to decode. You must pass the encrypted bytes in hexadecimal\n");
    }
    char* decryption = decrypt(argv[1]);
    printf("%s\n", decryption);
    return 0;
}
char* decrypt(char* cipherTextString) {
    paillier_ciphertext_t* ciphertext = paillier_create_enc_zero() ;
    mpz_init_set_str(ciphertext, cipherTextString, 16);

    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_BYTES);
    paillier_prvkey_t* privateKey = paillier_prvkey_from_hex(PRIVATE_KEY_BYTES, publicKey);

    paillier_plaintext_t* decryptedText = NULL;
    decryptedText = paillier_dec(decryptedText, publicKey, privateKey, ciphertext);
    char* decryptedTextString = paillier_plaintext_to_str(decryptedText);

    paillier_freeciphertext(ciphertext);
    paillier_freepubkey(publicKey);
    paillier_freeprvkey(privateKey);

    return  decryptedTextString;
}