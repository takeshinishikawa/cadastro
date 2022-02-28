/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_user.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:42:05 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:20:56 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/api.h"

static int callback(void *NotUsed, int argc, char **argv, char **azColName)
{
	int i;
	for(i = 0; i<argc; i++)
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	printf("\n");
	return 0;
}

int get_user_name(t_api_db *api_db, char *name)
{
	char	aux[300] = "SELECT * FROM REGISTER WHERE NAME='";
	char	sql[300];

	strcat(aux, name);
	strcat(aux, "';");
	strcpy(sql, aux);
	api_db->rc = sqlite3_exec(api_db->db, sql, callback, 0, &api_db->zErrMsg);
	if(api_db->rc != SQLITE_OK)
	{
		fprintf(stderr, "SQL error: %s\n", api_db->zErrMsg);
		sqlite3_free(api_db->zErrMsg);
	}
	else
		fprintf(stdout, "Operation done successfully\n");
	sqlite3_close(api_db->db);
	return 0;
}

int get_user_email(t_api_db *api_db, char *email)
{
	char	aux[300] = "SELECT * FROM REGISTER WHERE EMAIL='";
	char	sql[300];

	strcat(aux, email);
	strcat(aux, "';");
	strcpy(sql, aux);
	api_db->rc = sqlite3_exec(api_db->db, sql, callback, 0, &api_db->zErrMsg);
	if(api_db->rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", api_db->zErrMsg);
		sqlite3_free(api_db->zErrMsg);
	}
	else
		fprintf(stdout, "Operation done successfully\n");
	sqlite3_close(api_db->db);
	return 0;
}
