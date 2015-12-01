//testing file for UserDefinedFunctions in MySQL
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <my_global.h>
#include <my_sys.h>
#include <string.h>
#include <mysql.h>
#include <ctype.h>
#include <gmp.h>
#include <paillier.h>

my_bool testing_udf_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void testing_udf_deinit(UDF_INIT *initid __attribute__((unused)));
double  testing_udf(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)), char* is_null __attribute__((unused)), char* error __attribute__((unused)));

my_bool testing_udf_init(UDF_INIT *initid, UDF_ARGS *args, char *message){
	if(!(args->arg_count == 2)) {
		strcpy(message, "Expected two arguments --> for calculating sum ");
		return 1;
	}
	args->arg_type[0] = REAL_RESULT;
	args->arg_type[1] = REAL_RESULT;
	return 0;
}

void testing_udf_deinit(UDF_INIT *initid __attribute__((unused))){

}

double testing_udf(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)), char* is_null __attribute__((unused)), char* error __attribute__((unused))){
    double a = *((double *)(args->args[0]));
    double b = *((double *)(args->args[1]));
    paillier_pubkey_t** pub;
    paillier_prvkey_t** prv;
    paillier_get_rand_t get_rand;
	// paillier_keygen( 128, pub, prv, get_rand );

    return a-b;

}
