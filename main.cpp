#include <cstdlib>
#include <cstdio>
#include <vector>

#include "src/repository.h"
#include "src/Entities.h"
#include "src/Utils.h"
#include <postgresql/libpq-fe.h>
#include <cstring>

using std::vector;
using std::string;

const char *connection_template_info = "host=localhost port=5432 dbname=eagle_pay user=%.20s password=%.20s";

vector<std::string> separateSQLRequests(const char* filename) {
	FILE* file = fopen(filename, "r");
	vector<string> sqlRequests;
	if (file) {
		char line[1024];
		string currentRequest;
		while (fgets(line, sizeof(line), file)) {
			char* trimmedLine = line;
			while (*trimmedLine && strchr(" \t\r\n", *trimmedLine))
				++trimmedLine;
			size_t len = strlen(trimmedLine);
			while (len > 0 && strchr(" \t\r\n", trimmedLine[len - 1]))
				trimmedLine[--len] = '\0';
			if (len > 0 && strncmp(trimmedLine, "--", 2) != 0 && strncmp(trimmedLine, "/*", 2) != 0) {
				currentRequest += trimmedLine;
				if (trimmedLine[len - 1] == ';') {
					sqlRequests.push_back(currentRequest);
					currentRequest.clear();
				}
			}
		}
		fclose(file);
	} else {
		fprintf(stderr, "Unable to open file: %s\n", filename);
	}
	return sqlRequests;
}

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
		exit(1);
	}
	vector<string> requests(separateSQLRequests("../database.sql"));
	for (const auto & request : requests) {
		PGresult *result = PQexec(connection, request.c_str());
		if (!result)
			fprintf(stderr, "Fatal error executing command %s\nPGresult was NULL\n", request.c_str());
		else {
			if (PQresultStatus(result) == PGRES_FATAL_ERROR) {
				char *errmsg = PQresultErrorMessage(result);
				fprintf(stderr, "ERROR executing request \"%s\"\n%s\n", request.c_str(), errmsg);
			}
		}
		PQclear(result);
	}
	PQfinish(connection);
	return 0;
}
