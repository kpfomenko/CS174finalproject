#include "encyptedSum.h"
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

my_bool sum_he_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    char* sum = (char*) malloc(sizeof(char) * ENCRYPTION_BYTE_LENGTH);
    initid->ptr = sum;

    if(!(args->arg_count == 1)) {
        strcpy(message, "Expected one argument for calculating sum ");
        return 1;
    }
    if(	args->arg_type[0] != STRING_RESULT){
        strcpy(message, "sum_he requires an string containing the hexidecimal encrypted value");
        return 1;
    }

    return 0;
}

void sum_he_deinit(UDF_INIT *initid) {
    free(initid->ptr);
}

char *sum_he(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {
//    memcpy(result, initid->ptr, ENCRYPTION_BYTE_LENGTH);
//    *length = ENCRYPTION_BYTE_LENGTH;
//    return result;
    return "hi";
}

void sum_he_clear(UDF_INIT *initid, char *is_null, char *error) {
    initid->ptr = NULL;
}

void sum_he_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {

    if(!(args->arg_count == 1)) {
        strcpy(error, "Expected one argument for calculating sum ");
        return;
    }
    if(	args->arg_type[0] != STRING_RESULT){
        strcpy(error, "sum_he requires an string containing the hexidecimal encrypted value");
        return;
    }

    char* encryptedHex1 = initid->ptr;
    char* encryptedHex2 = args->args[0];

    unsigned char* encryptedBytes1 = convertHexToBytes(encryptedHex1);
    unsigned char* encryptedBytes2 = convertHexToBytes(encryptedHex2);

    paillier_ciphertext_t* ciphertext1 = paillier_ciphertext_from_bytes(encryptedBytes1, ENCRYPTION_BYTE_LENGTH);
    paillier_ciphertext_t* ciphertext2 = paillier_ciphertext_from_bytes(encryptedBytes2, ENCRYPTION_BYTE_LENGTH);

    paillier_ciphertext_t* result = paillier_create_enc_zero();
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_mul(publicKey, result, ciphertext1, ciphertext2);

    unsigned char* resultBytes = paillier_ciphertext_to_bytes(ENCRYPTION_BYTE_LENGTH, result);
    char* resultHex = convertBytesToHex(resultBytes);

//    free(initid->ptr);
    initid->ptr = (char*) resultHex;
//    memcpy(initid->ptr, resultHex, ENCRYPTION_BYTE_LENGTH);
//    memcpy(initid->ptr, "hello\0", 7);
//    initid->ptr = "hello";

//    free(encryptedBytes1);
//    free(encryptedBytes2);
//    free(resultBytes);
//    paillier_freeciphertext(ciphertext1);
//    paillier_freeciphertext(ciphertext2);
//    paillier_freeciphertext(result);
//    paillier_freepubkey(publicKey);
}

unsigned char *convertHexToBytes(char *hex) {
    unsigned char* encryptedBytes = (unsigned char*) malloc(sizeof(unsigned char) * ENCRYPTION_BYTE_LENGTH);

    // Parsing through hex to build byte array
    char* hexPortion = strtok(hex, ":");
    int i = 0;
    while(hexPortion != NULL){
        encryptedBytes[i] = strtol(hexPortion, NULL, 16);
        hexPortion = strtok(NULL, ":");
        i++;
    }

    return encryptedBytes;
}

char *convertBytesToHex(unsigned char *bytes) {
    char* hex = (char*) malloc(2*ENCRYPTION_BYTE_LENGTH + 1);
    int i;
    for (i = 0; i < ENCRYPTION_BYTE_LENGTH; i++){
        if (i > 0) {
            hex += sprintf(hex, ":");
        }
        hex += sprintf(hex, "%02X", bytes[i]);
    }
    hex += sprintf(hex, "\n");
    return hex;
}
