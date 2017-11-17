/*
Homepage: http://netkiller.github.io/
Author: netkiller<netkiller@msn.com>
*/
#include <stdlib.h>
#include <stdio.h>
#include <mysql.h>
#include <string.h>
#include <sys/io.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>

#include "outfile.h"

/* ------------------------ outfile_create ----------------------------- */

my_bool outfile_create_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

  if (args->arg_count != 1)
  {
    strncpy(message,
            "one arguments must be supplied: outfile_create('<pipename>').",
            MYSQL_ERRMSG_SIZE);
    return 1;
  }
  args->arg_type[0]= STRING_RESULT;

  return 0;
}

char *outfile_create(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

    char *status;
	if (create_outfile(args->args[0]) == 0)
        status = "ture";
    else
		status = "false";

    *length = strlen(status);
    return ((char *)status);

}

void outfile_create_deinit(UDF_INIT *initid)
{
  return;
}

/* ------------------------ outfile_remove ----------------------------- */

my_bool outfile_remove_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

  if (args->arg_count != 1)
  {
    strncpy(message,"one arguments must be supplied: outfile_remove('<pipename>').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;

  return 0;
}

char *outfile_remove(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

    char *data;
	if( remove_outfile(args->args[0]) == 0 )
		data = "true";
	else
		//asprintf(&data, "ARG0=%s, ARG1=%d", args->args[0], errno);
		data = "false";
		
    *length = strlen(data);
    return ((char *)data);

}

void outfile_remove_deinit(UDF_INIT *initid)
{
  return;
}

/* ------------------------ outfile_read ----------------------------- */

my_bool outfile_read_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{

  if (args->arg_count != 1)
  {
    strncpy(message, "one arguments must be supplied: outfile_read('<pipename>').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;

  return 0;
}

char *outfile_read(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

    char *data;

	data = read_outfile(args->args[0]);

	//asprintf(&data, "ARG0=%s, ARG1=%d", args->args[0], args->args[1]);
    *length = strlen(data);
    return ((char *)data);

}

void outfile_read_deinit(UDF_INIT *initid)
{
  return;
}

/* ------------------------ outfile_write ----------------------------- */

my_bool outfile_write_init(UDF_INIT *initid, UDF_ARGS *args, char *message)
{
  if (args->arg_count != 2)
  {
    strncpy(message, "two arguments must be supplied: outfile_write('pipename','message').", MYSQL_ERRMSG_SIZE);
    return 1;
  }

  args->arg_type[0]= STRING_RESULT;
    return 0;
}

char *outfile_write(UDF_INIT *initid, UDF_ARGS *args,
                __attribute__ ((unused)) char *result,
               unsigned long *length,
                __attribute__ ((unused)) char *is_null,
                __attribute__ ((unused)) char *error)
{

	char *status;
  //asprintf(&status, "SAFENET_URL=%s, SAFENET_KEY=%s", safe_url, safe_key);
	if( write_outfile( args->args[0], args->args[1] ) == -1)
		status = "false";
	else
		status = "true";
  
	*length = strlen(status);
	return ((char *)status);
}

void outfile_write_deinit(UDF_INIT *initid)
{
   return;
}
