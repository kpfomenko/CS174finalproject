
#include "sum.h"
#include <string.h>

my_bool mySum_init(UDF_INIT *initid, UDF_ARGS *args, char *message){
	longlong* sum = (longlong *)malloc(sizeof(longlong));
	*sum = 0;

	initid->ptr = (char *)sum;

	if(!(args->arg_count == 1)) {
		strcpy(message, "Expected one argument --> for calculating sum ");
		return 1;
	}
	if(	args->arg_type[0] != INT_RESULT){
		strcpy(message, "mySum requires an integer");
		return 1;
	}
	return 0;
}

void mySum_deinit(UDF_INIT *initid){
	free(initid->ptr);
}

longlong mySum(UDF_INIT* initid, UDF_ARGS* args __attribute__((unused)), char* is_null __attribute__((unused)),
               char* error __attribute__((unused))){
    return  *((longlong *) initid->ptr);
}

void mySum_add(UDF_INIT *initid, UDF_ARGS *args, char *is_null, char *error){
	*((longlong *) initid->ptr) = *((longlong *) initid->ptr) + *((longlong *) args->args[0]);	
}

void mySum_clear(UDF_INIT *initid, char *is_null, char *error){
	*((longlong *) initid->ptr) = 0;
}

