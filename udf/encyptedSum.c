#include <string.h>
#include "encyptedSum.h"
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

my_bool sum_he_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    paillier_ciphertext_t* sum  = paillier_create_enc_zero();
    initid->ptr = (char *)sum;

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
    // free(initid->ptr);
    paillier_freeciphertext((paillier_ciphertext_t *) initid->ptr);
}

char *sum_he(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {
    //conversion to string
    paillier_ciphertext_t* ciphertext = (paillier_ciphertext_t *) initid->ptr ;

    int sizeOfResult = mpz_sizeinbase(ciphertext,10) + 2;
    char* encrypted = (char*)malloc(sizeof(char)*sizeOfResult);
    mpz_get_str(encrypted, 10, ciphertext);
    memcpy(result, encrypted, sizeOfResult);
    *length = sizeOfResult; 
    return result;
    // return "hello";

}

void sum_he_clear(UDF_INIT *initid, char *is_null, char *error) {
    paillier_freeciphertext((paillier_ciphertext_t *) initid->ptr);
    *((paillier_ciphertext_t *) initid->ptr) = * paillier_create_enc_zero();
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

    paillier_ciphertext_t* ciphertext1 = (paillier_ciphertext_t *) initid->ptr ;
    paillier_ciphertext_t* ciphertext2 = paillier_create_enc_zero() ;
    mpz_init_set_str(ciphertext2, (char *) args->args[0], 10);

    paillier_ciphertext_t* result = paillier_create_enc_zero();
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_mul(publicKey, result, ciphertext1, ciphertext2);

    // paillier_freeciphertext(ciphertext1);
    *((paillier_ciphertext_t *) initid->ptr) = *result;

    paillier_freeciphertext(ciphertext2);
    paillier_freepubkey(publicKey);
}
