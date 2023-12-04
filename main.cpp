#include <cstdlib>
#include <cstdio>
#include "src/repository.h"
#include "src/Entities.h"
#include "src/Utils.h"
#include <postgresql/libpq-fe.h>

const char *connection_template_info = "host=localhost port=5432 dbname=eagle_pay user=%.20s password=%.20s";

int main()
{
	char *user = getenv("USER");
	if (!user) {
		printf("Environment variable USER not set.");
		return 1;
	}
	char *password = getenv("PASSWORD");
	if (!password) {
		printf("Environment variable PASSWORD not set.");
		return 1;
	}
	PGconn * connection;
	char connection_info[100];
	sprintf(connection_info, connection_template_info, user, password);
	connection = PQconnectdb(connection_info);
	if (PQstatus(connection) != CONNECTION_OK) {
		fprintf(stderr, "Connection to database failed %s\n", PQerrorMessage(connection));
	}
	PQfinish(connection);
	return 0;
}
