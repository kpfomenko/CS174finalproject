//
// Created by Deanna Hartsook on 11/29/15.
//

#include "sum.h"

long long MySum(UDF_INIT *initid, UDF_ARGS *args,
          char *is_null, char *error) {
    return 10;
}

my_bool MySum_init(UDF_INIT *initid, UDF_ARGS *args, char *message) {
    return 0;
}

void MySum_deinit(UDF_INIT *initid) {

}
