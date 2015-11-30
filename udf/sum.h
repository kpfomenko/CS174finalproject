//
// Created by Deanna Hartsook on 11/29/15.
//

#ifndef CS174FINALPROJECT_SUM_H
#define CS174FINALPROJECT_SUM_H

#include <mysql.h>

long long MySum(UDF_INIT *initid, UDF_ARGS *args,
              char *is_null, char *error);

my_bool MySum_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

void MySum_deinit(UDF_INIT *initid);

#endif //CS174FINALPROJECT_SUM_H
