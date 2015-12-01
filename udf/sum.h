//
// Implementation of aggregate sum function.
//

#ifndef CS174FINALPROJECT_SUM_H
#define CS174FINALPROJECT_SUM_H

#include <mysql.h>
#include <my_global.h>

longlong MySum(UDF_INIT *initid, UDF_ARGS *args,
              char *is_null, char *error);

my_bool MySum_init(UDF_INIT *initid, UDF_ARGS *args, char *message);

void MySum_deinit(UDF_INIT *initid);

void MySum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error);

void MySum_clear(UDF_INIT *initid, char *is_null, char *error);

#endif //CS174FINALPROJECT_SUM_H
