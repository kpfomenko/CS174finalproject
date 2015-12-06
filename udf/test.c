#include <string.h>
#include "encyptedSum.h"
#include "gmp.h"
#include "../libpaillier-0.8/paillier.h"

int main(){

    char* text1 = "47568167471551563428364107204485061728325271811180955259977782559963226005888"; //10
    char* text2 = "31608052274259151569895581162442755688527891042387631204563155239473282588025"; //11

    paillier_ciphertext_t* ciphertext1 = paillier_create_enc_zero() ;
    paillier_ciphertext_t* ciphertext2 = paillier_create_enc_zero() ;
    mpz_init_set_str(ciphertext1, text1, 10);
    mpz_init_set_str(ciphertext2, text2, 10);

    paillier_ciphertext_t* result = paillier_create_enc_zero();
    paillier_pubkey_t* publicKey = paillier_pubkey_from_hex(PUBLIC_KEY_HEX);
    paillier_mul(publicKey, result, ciphertext1, ciphertext2);

    int sizeOfResult = mpz_sizeinbase(result,10);
    char* encrypted = (char*)malloc(sizeof(char)*(sizeOfResult + 2));
    mpz_get_str(encrypted, 10, result);


    printf("Result: %s\n", encrypted);

    paillier_freeciphertext(ciphertext2);
    paillier_freepubkey(publicKey);

}
