//
// Computes the sum of two encrypted values (passed in as hex)
//

#ifndef CS174FINALPROJECT_ENCYPTEDSUM_H
#define CS174FINALPROJECT_ENCYPTEDSUM_H

#include <mysql.h>
#include <my_global.h>

static const int ENCRYPTION_BYTE_LENGTH = 128;
static char*PUBLIC_KEY_HEX = "a810ae51ace032a8b8743a9ef0baa51d";

my_bool sum_he_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void sum_he_deinit(UDF_INIT *initid __attribute__((unused)));
char *sum_he(UDF_INIT *initid, UDF_ARGS *args, char *result, unsigned long *length, char *is_null, char *error);
void sum_he_clear(UDF_INIT *initid, char *is_null, char *error);
void sum_he_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

#endif //CS174FINALPROJECT_ENCYPTEDSUM_H
