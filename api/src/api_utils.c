/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/27 17:55:29 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:24:47 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/api.h"

void log_message(const char *filename, struct mg_http_message *hm, struct mg_str host, int status)
{
	int		fd;
	time_t	time_object;
	struct	tm raw_time;
	char	*aux;
	char	*method;

	time_object = time(NULL);
	raw_time = *localtime(&time_object);
	fd = open(filename, O_CREAT | O_APPEND | O_RDWR, 0644);
	if (fd < 0)
		return;
	aux = strtok((char *)hm->method.ptr, "\n");
	method = strtok((char *)aux, " ");
	dprintf(fd,
			"%02d:%02d:%02d %02d/%02d/%02d %d %-7s %s\n",
			raw_time.tm_hour, raw_time.tm_min, raw_time.tm_sec,
			raw_time.tm_mday, raw_time.tm_mon + 1, raw_time.tm_year + 1900,
			status,
			method,
			strtok((char *)hm->query.ptr, " "));
	close(fd);
}

size_t	line_len(char	*line)
{
	size_t	i;

	i = 0;
	while (line[i] != '\n')
		i++;
	return (i);
}

void	free_struct(t_info	*info)
{
	if (info->name)
		free(info->name);
	if (info->email)
		free(info->email);
	if (info->password)
		free(info->password);
	free(info);
}

void init_server_struct(t_api *api)
{
	mg_mgr_init(&api->mgr);
	api->got_data = false;
}
