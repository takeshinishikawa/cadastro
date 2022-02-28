/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_table.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 13:04:39 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:23:51 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/api.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int		i;
	for(i = 0; i<argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

void init_db(t_api_db *api_db)
{
	api_db->zErrMsg = 0;
	api_db->rc = sqlite3_open("database/api.db", &api_db->db);
	if (api_db->rc)
	{
		fprintf(stderr, "Can't open database: %s\n", sqlite3_errmsg(api_db->db));
		return ;
	}

	char	*sql;

	sql = "CREATE TABLE REGISTER("  \
	"EMAIL TEXT PRIMARY KEY     NOT NULL," \
	"NAME           TEXT    NOT NULL," \
	"PASSWORD       TEXT );";
	api_db->rc = sqlite3_exec(api_db->db, sql, callback, 0, &api_db->zErrMsg);
	if(api_db->rc != SQLITE_OK )
		sqlite3_free(api_db->zErrMsg);
	return;
}
