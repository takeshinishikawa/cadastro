/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   api.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/23 18:11:07 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/27 22:10:09 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef API_H
# define API_H

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <stdlib.h>
# include <stddef.h>
# include <time.h>
# include "mongoose.h"
# include "libft.h"

# include <dlfcn.h>
# include "../src/sqlite3.h"




static const char *s_debug_level = "2";
static const char *s_listening_address = "http://0.0.0.0:8000/";
static const char *s_root_dir = ".";


typedef struct	s_info
{
	char	*name;
	char	*email;
	char	*password;
	int		is_valid;
}			t_info;

typedef struct	s_api
{
	struct mg_mgr	mgr;
	bool			got_data;
}				t_api;

typedef struct	s_api_db
{
	sqlite3	*db;
	char *zErrMsg;
	int rc;
}				t_api_db;

void init_db(t_api_db *api_db);
int insert_table(t_api_db *api_db, char *name, char *email, char *password);
int get_user_name(t_api_db *api_db, char *name);
int get_user_email(t_api_db *api_db, char *email);
int update_password(t_api_db *api_db, char *email, char *password);
int delete_user(t_api_db *api_db, char *email, char *password);
void init_log_db(t_api_db *api_db);
int insert_log(t_api_db *api_db, const char *hm, int status, t_info *info);
void log_message(const char *filename, struct mg_http_message *hm, struct mg_str host, int status);
size_t	line_len(char	*line);
void	free_struct(t_info	*info);
void init_server_struct(t_api *api);



#endif
