/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:42:05 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:23:37 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/api.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int	i;
	for(i = 0; i<argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

int insert_table(t_api_db *api_db, char *name, char *email, char *password)
{
	char	aux[300] = "INSERT INTO REGISTER (EMAIL,NAME,PASSWORD) "  \
         "VALUES ('";
	char	sql[300];

	strcat(aux, email);
	strcat(aux, "', '");
	strcat(aux, name);
	strcat(aux, "', '");
	strcat(aux, password);
	strcat(aux, "' ); ");
	strcpy(sql, aux);
	api_db->rc = sqlite3_exec(api_db->db, sql, callback, 0, &api_db->zErrMsg);
	if(api_db->rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", api_db->zErrMsg);
		sqlite3_free(api_db->zErrMsg);
	}
	else
		fprintf(stdout, "Records created successfully\n");
	sqlite3_close(api_db->db);
	return 0;
}
