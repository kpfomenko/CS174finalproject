//
// Created by Deanna Hartsook on 11/29/15.
//

#ifndef CS174FINALPROJECT_SUM_H
#define CS174FINALPROJECT_SUM_H

#include <mysql.h>
#include <my_global.h>

my_bool mySum_init(UDF_INIT *initid, UDF_ARGS *args, char *message);
void mySum_deinit(UDF_INIT *initid __attribute__((unused)));
longlong  mySum(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)), char* is_null __attribute__((unused)), char* error __attribute__((unused)));
void mySum_clear(UDF_INIT *initid, char *is_null, char *error);
void mySum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

#endif //CS174FINALPROJECT_SUM_H
