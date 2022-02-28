/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   delete_user.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:42:05 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:23:15 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/api.h"

static int callback(void *data, int argc, char **argv, char **azColName)
{
	int		i;
	fprintf(stderr, "%s: ", (const char*)data);

	for(i = 0; i<argc; i++)
	{
		printf("%s = %s\n", azColName[i], argv[i] ? argv[i] : "NULL");
	}
	printf("\n");
	return 0;
}

int delete_user(t_api_db *api_db, char *email, char *password)
{
	char	aux[300] = "DELETE FROM REGISTER WHERE EMAIL='";
	char	sql[300];

	strcat(aux, email);
	strcat(aux, "' AND PASSWORD='");
	strcat(aux, password);
	strcat(aux, "'; SELECT * from REGISTER;");
	strcpy(sql, aux);
	api_db->rc = sqlite3_exec(api_db->db, sql, callback, 0, &api_db->zErrMsg);
	if(api_db->rc != SQLITE_OK ){
		fprintf(stderr, "SQL error: %s\n", api_db->zErrMsg);
		sqlite3_free(api_db->zErrMsg);
	} else {
		fprintf(stdout, "Records updated successfully\n");
	}
	sqlite3_close(api_db->db);
	return 0;
}
