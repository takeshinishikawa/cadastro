#include "cli.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	printf("\n");
	for(i = 0; i<argc; i++)
	{
		printf("|%25s|", argv[i]);
	}
	return 0;
}

int get_user_name(t_log_db *log_db, const char *email)
{
	char	aux[300] = "SELECT name FROM LOG WHERE email='";
	char	sql[300];

	strcat(aux, email);
	strcat(aux, "';");
	strcpy(sql, aux);
	printf("___________________________\n");
	printf("|%25s|\n", "name");
	printf("---------------------------");
	log_db->rc = sqlite3_exec(log_db->db, sql, callback, 0, &log_db->zErrMsg);
	printf("\n---------------------------\n");
	if(log_db->rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", log_db->zErrMsg);
		sqlite3_free(log_db->zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(log_db->db);
	return 0;
}

int get_user_email(t_log_db *log_db, const char *name)
{
	char	aux[300] = "SELECT email FROM LOG WHERE name='";
	char	sql[300];

	strcat(aux, name);
	strcat(aux, "';");
	strcpy(sql, aux);
	printf("___________________________\n");
	printf("|%25s|\n", "Name");
	printf("---------------------------");
	log_db->rc = sqlite3_exec(log_db->db, sql, callback, 0, &log_db->zErrMsg);
	printf("\n---------------------------\n");
	if(log_db->rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", log_db->zErrMsg);
		sqlite3_free(log_db->zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(log_db->db);
	return 0;
}

int get_method(t_log_db *log_db)
{
	char sql[300] = "SELECT method, COUNT (*) FROM LOG GROUP BY method;";
	printf("______________________________________________________\n");
	printf("|%25s|", "Method");
	printf("|%25s|\n", "Total requests");
	printf("------------------------------------------------------");
	log_db->rc = sqlite3_exec(log_db->db, sql, callback, 0, &log_db->zErrMsg);
	printf("\n------------------------------------------------------\n");
	if(log_db->rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", log_db->zErrMsg);
		sqlite3_free(log_db->zErrMsg);
	} else {
		fprintf(stdout, "Operation done successfully\n");
	}
	sqlite3_close(log_db->db);
	return 0;
}

int get_status(t_log_db *log_db)
{
	char sql[300] = "SELECT status, COUNT (*) FROM LOG GROUP BY status;";
	printf("______________________________________________________\n");
	printf("|%25s|", "Status Code");
	printf("|%25s|\n", "Total requests");
	printf("------------------------------------------------------");
	log_db->rc = sqlite3_exec(log_db->db, sql, callback, 0, &log_db->zErrMsg);
	printf("\n------------------------------------------------------\n");
	if(log_db->rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", log_db->zErrMsg);
		sqlite3_free(log_db->zErrMsg);
	}
	sqlite3_close(log_db->db);
	return 0;
}

int main(int argc, const char **argv)
{
	t_log_db	log_db;

	switch (argc)
	{
		case 1:
		{
			fprintf(stdout, "%s", HELP);
			return EXIT_SUCCESS;
			break;;
		}
		default:
		{
			log_db.rc = sqlite3_open(DATABASE_PATH, &log_db.db);
			init_log_db(&log_db);
			if (strcmp(argv[1], "method") == 0)
			{
				get_method(&log_db);
				return (1);
			}
			else if (strcmp(argv[1], "email") == 0)
			{
				if (argc == 3)
					get_user_name(&log_db, argv[2]);
				return (1);
			}
			else if (strcmp(argv[1], "name") == 0)
			{
				if (argc == 3)
					get_user_email(&log_db, argv[2]);
				return (1);
			}
			else if (strcmp(argv[1], "status") == 0)
			{
				get_status(&log_db);
				return (1);
			}
			else
			{
				fprintf(stderr, "%s", HELP);
				return EXIT_FAILURE;
			}
			break;
			sqlite3_close(log_db.db);
		}
	}
}
