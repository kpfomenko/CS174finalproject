#include <string.h>
#include "encyptedSum.h"
#include "gmp.h"
#include "paillier.h"

// Initializes the initid->ptr to point to a newly allocated ciphertext.
my_bool sum_he_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    paillier_ciphertext_t* sum  = paillier_create_enc_zero();
    initid->ptr = (char *) sum;

    //Error Handling
    if(args->arg_count != 1) {
        strcpy(message, "Expected one argument for calculating sum ");
        return 1;
    }
    if(	args->arg_type[0] != STRING_RESULT){
        strcpy(message, "SUM_HE requires a TEXT string containing the encrypted value as input.");
        return 1;
    }

    return 0;
}

//Frees the initid->ptr ciphertext 
void sum_he_deinit(UDF_INIT *initid) {
    paillier_freeciphertext((paillier_ciphertext_t *) initid->ptr);
}

//Gets the encrypted sum from the initid->ptr and copies it into the result variable and sets the *length variable.
char *sum_he(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error) {
    paillier_ciphertext_t* ciphertext = (paillier_ciphertext_t *) initid->ptr ;
    int sizeOfResult = mpz_sizeinbase(ciphertext->c,10) + 2;
    char* encrypted = mpz_get_str(NULL, 10, ciphertext->c);
    memcpy(result, encrypted, sizeOfResult);
    *length = sizeOfResult;
    return result;

}
// Clears the memory pointed to by the initid->ptr, and reinitializes it to an empty ciphertext.
void sum_he_clear(UDF_INIT *initid, char *is_null, char *error) {
    paillier_freeciphertext((paillier_ciphertext_t *) initid->ptr);
    *((paillier_ciphertext_t *) initid->ptr) = * paillier_create_enc_zero();
}

// Performs the main addition of the SUM_HE function where it takes two ciphertexts,
// multiples them using the paillier_mult() function, and then returns then sets the
// initid->ptr to point to this new sum.
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
    mpz_init_set_str(ciphertext2->c, args->args[0], 10);

    paillier_ciphertext_t* result = paillier_create_enc_zero();
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_mul(publicKey, result, ciphertext1, ciphertext2);

    initid->ptr = (char*) result;

    paillier_freeciphertext(ciphertext2);
    paillier_freepubkey(publicKey);
}
