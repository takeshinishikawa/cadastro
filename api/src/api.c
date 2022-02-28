/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/25 17:45:22 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 21:24:24 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/api.h"

// Handle interrupts, like Ctrl-C
static int s_signo = 0;

static void signal_handler(int signo)
{
	s_signo = signo;
	write(1, "\n", 1);
}

int	get_info(struct mg_connection *c, t_info *info)
{
	char	*aux;

	info->name = NULL;
	info->email = NULL;
	info->password = NULL;

	if (!c->recv.buf)
	{
		info->is_valid = 0;
		return (1);
	}
	aux = strdup(c->recv.buf);
	if (strstr(aux, "name: ") != NULL)
	{
		info->name = malloc(sizeof(char) * (line_len(strstr(aux, "name: ") + 6) + 1));
		ft_strlcpy(info->name, strstr(aux, "name: ") + 6, line_len(strstr(aux, "name: ") + 6));
	}
	if (strstr(aux, "email: ") != NULL)
	{
		info->email = malloc(sizeof(char) * (line_len(strstr(aux, "email: ") + 7) + 1));
		ft_strlcpy(info->email, strstr(aux, "email: ") + 7, line_len(strstr(aux, "email: ") + 7));
	}
	if (strstr(aux, "password: ") != NULL)
	{
		info->password = malloc(sizeof(char) * (line_len(strstr(aux, "password: ") + 10) + 1));
		ft_strlcpy(info->password, strstr(aux, "password: ") + 10, line_len(strstr(aux, "password: ") + 10));
	}
	free(aux);
	if (info->name == NULL || info->email == NULL || info->password == NULL)
	{
		info->is_valid = 0;
		return (1);
	}
	info->is_valid = 1;
	return (0);
}

// We use the same event handler function for HTTP and HTTPS connections
// fn_data is NULL for plain HTTP, and non-NULL for HTTPS
static void create_server(struct mg_connection *c, int ev, void *ev_data, void *fn_data)
{
	char		*data = NULL;
	t_api_db	api_db;
	t_api_db	log_db;
	int			status;
	struct		mg_str host = mg_url_host(s_listening_address);
	bool		correct_uri;


	init_db(&api_db);
	init_log_db(&log_db);
	if (ev == MG_EV_HTTP_MSG)
	{
		struct	mg_http_message	*hm = (struct mg_http_message *)ev_data;
		t_info	*info;

		correct_uri = mg_http_match_uri(hm, "/");
		status = 200;
		info = malloc(sizeof(t_info));
		get_info(c, info);

		if (!strncmp(hm->method.ptr, "GET", 3) && correct_uri && (info->name != NULL \
		|| info->email != NULL))
		{
			if (info->name != NULL)
				get_user_name(&api_db, info->name);
			if (info->email != NULL)
				get_user_email(&api_db, info->email);
			mg_http_reply(c, status, \
						"Content-Type: application/json\r\n", \
						"{\n\"name\": \"%s\",\n\"email\": \"%s\",\n\"password\": \"%s\"\n}\n", \
			info->name, info->email, info->password);
		}
		else if (!strncmp(hm->method.ptr, "PUT", 3) && correct_uri && info->is_valid == 1)
		{
			update_password(&api_db, info->email, info->password);
			mg_http_reply(c, status, \
						"Content-Type: application/json\r\n", \
						"{\n\"name\": \"%s\",\n\"email\": \"%s\",\n\"password\": \"%s\"\n}\n", \
			info->name, info->email, info->password);
		}
		else if (!strncmp(hm->method.ptr, "POST", 4) && correct_uri && info->is_valid == 1)
		{
			insert_table(&api_db, info->name, info->email, info->password);
			mg_http_reply(c, status, \
						"Content-Type: application/json\r\n", \
						"{\n\"name\": \"%s\",\n\"email\": \"%s\",\n\"password\": \"%s\"\n}\n", \
			info->name, info->email, info->password);
		}
		else if (!strncmp(hm->method.ptr, "DELETE", 6) && correct_uri && (info->email != NULL \
			&& info->password != NULL))
		{
			delete_user(&api_db, info->email, info->password);
			mg_http_reply(c, status, \
						"Content-Type: application/json\r\n", \
						"{\n\"name\": \"%s\",\n\"email\": \"%s\",\n\"password\": \"%s\"\n}\n", \
			info->name, info->email, info->password);
		}
		else
		{
			status = 400;
			mg_http_reply(c, status, "", "Bad Request", hm->method.ptr);
		}
		log_message("log/log.txt", hm, host, status);
		insert_log(&log_db, hm->method.ptr, status, info);
		free_struct(info);
	}
	sqlite3_close(api_db.db);
	sqlite3_close(log_db.db);
	(void)fn_data;
}

int run_server(t_api *api)
{
	struct		mg_connection *c;
	char		path[MG_PATH_MAX] = ".";

	if (strchr(s_root_dir, ',') == NULL)
	{
		realpath(s_root_dir, path);
		s_root_dir = path;
	}
	init_server_struct(api);
	if ((c = mg_http_listen(&api->mgr, s_listening_address, create_server, api)) == NULL) // Create HTTP listener
	{
		MG_ERROR(("Cannot listen on %s",
				  s_listening_address));
		return (1);
	}
	MG_INFO(("Mongoose version : v%s", MG_VERSION));
	MG_INFO(("Listening on     : %s", s_listening_address));
	MG_INFO(("Web root         : [%s]", s_root_dir));
	signal(SIGINT, &signal_handler);
	while (s_signo == 0)
		mg_mgr_poll(&api->mgr, 1000);
	MG_INFO(("Exiting on signal %d", s_signo));
	return 0;
}

int main(int argc, char *argv[])
{
	t_api	api;

	run_server(&api);
	mg_mgr_free(&api.mgr);
	return (EXIT_SUCCESS);
}
