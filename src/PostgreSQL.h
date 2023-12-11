/* Written by Kyrylo Pervushyn on 12/10/23 */
#ifndef EAGLEPAY0_POSTGRESQL_H
#define EAGLEPAY0_POSTGRESQL_H

#ifdef _WIN32
/* Include PostgreSQLode for WINDOWS */
#include <libpq-fe.h>
#pragma warning(disable : 4996)
#else
/* Same code for linux */
#include <postgresql/libpq-fe.h>
#endif

const char *db_file = "../database.sql";
const char *connection_template_info = "host=localhost port=5432 dbname=eagle_pay user=%.20s password=%.20s";

#endif //EAGLEPAY0_POSTGRESQL_H
