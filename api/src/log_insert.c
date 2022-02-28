/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   log_insert.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 14:42:05 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:25:03 by rtakeshi         ###   ########.fr       */
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

int insert_log(t_api_db *api_db, const char *hm, int status, t_info *info)
{
	time_t	time_object;
	struct	tm raw_time;
	char	timestamp[20];

	time_object = time(NULL);
	raw_time = *localtime(&time_object);
	snprintf(timestamp, 20,
			"%02d:%02d:%02d %02d/%02d/%02d",
			raw_time.tm_hour, raw_time.tm_min, raw_time.tm_sec,
			raw_time.tm_mday, raw_time.tm_mon + 1, raw_time.tm_year + 1900);

	char	aux[300] = "INSERT INTO LOG (timestamp,method,\
	status,email,name) "  \
         "VALUES ('";
	char	sql[300];
	char	*str_status;

	str_status = ft_itoa(status);
	strcat(aux, timestamp);
	strcat(aux, "', '");
	strcat(aux, hm);
	strcat(aux, "', '");
	strcat(aux, str_status);
	strcat(aux, "', '");
	if (info->email != NULL)
		strcat(aux, info->email);
	else
		strcat(aux, "Bad request. No email.");
	strcat(aux, "', '");
	if (info->name != NULL)
		strcat(aux, info->name);
	else
		strcat(aux, "Bad request. No email.");
	strcat(aux, "' ); ");
	strcpy(sql, aux);
	api_db->rc = sqlite3_exec(api_db->db, sql, callback, 0, &api_db->zErrMsg);
	if(api_db->rc != SQLITE_OK )
	{
		fprintf(stderr, "SQL error: %s\n", api_db->zErrMsg);
		sqlite3_free(api_db->zErrMsg);
	}
	else
		fprintf(stdout, "Log create successfully\n");
	sqlite3_close(api_db->db);
	free(str_status);
	return 0;
}
