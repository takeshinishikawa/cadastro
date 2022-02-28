/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_create_table.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:04:39 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 19:41:55 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/cli.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
	{
	int i;
	for(i = 0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

void init_log_db(t_log_db *log_db)
{
	log_db->zErrMsg = 0;
	log_db->rc = sqlite3_open(DATABASE_PATH, &log_db->db);
	if (log_db->rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(log_db->db));
		return ;
	}
	/*else
		fprintf(stderr, "Opened database successfully\n");*/

	char	*sql;

	sql = "CREATE TABLE LOG("  \
	"timestamp TEXT PRIMARY KEY     NOT NULL," \
	"method       TEXT    NOT NULL," \
	"status       INT     NOT NULL," \
	"email        TEXT    NOT NULL," \
	"name         TEXT    NOT NULL );";

	/* Execute SQL statement */
	log_db->rc = sqlite3_exec(log_db->db, sql, callback, 0, &log_db->zErrMsg);

	if(log_db->rc != SQLITE_OK )
	{
		//fprintf(stderr, "SQL error: %s\n", log_db->zErrMsg);
		sqlite3_free(log_db->zErrMsg);
	}
	/*else
		fprintf(stdout, "Table created successfully\n");*/
	return;
}
