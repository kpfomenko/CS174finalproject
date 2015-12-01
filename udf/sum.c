#include <string.h>
#include "sum.h"

long long MySum(UDF_INIT *initid, UDF_ARGS *args,
          char *is_null, char *error) {

    return *((longlong *) initid->ptr);
}

my_bool MySum_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    longlong * sum = (longlong *) malloc(sizeof(longlong));
    *sum = 0;

    initid->ptr = (char*) sum;

    if (args->arg_count != 1)
    {
        strcpy(message,"MyTest() requires one arguments");
        return 1;
    }

    return 0;
}

void MySum_deinit(UDF_INIT *initid) {
    free(initid->ptr);
}

void MySum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error) {
    *((longlong*)initid->ptr) = *((longlong*)initid->ptr) +
                                *((longlong*)args->args[0]);
}

void MySum_clear(UDF_INIT *initid, char *is_null, char *error) {
    *((longlong *) initid->ptr) = 0;
}
