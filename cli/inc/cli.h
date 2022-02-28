#ifndef cli_h
#define cli_h

# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <stdarg.h>
# include <string.h>
# include <errno.h>
# include <stddef.h>
# include <time.h>
# include "libft.h"




# include <dlfcn.h>
# include "../src/sqlite3.h"

static const char *DATABASE_PATH = "../api/database/log.db";
static sqlite3 *DATABASE;

static const char *HELP = "\n"
"\n"
"\n"

"Created by rtakeshi\n"
"rtakeshi@student.42sp.org.br\n"
"\n"
"\n"
"\e[1mGENERAL USAGE\e[0m\n"
"\e[32mcli42\n"
"    \e[32mhelp\e[0m                                 show OPTIONS\n"
"\e[32mcli42\n"
"    \e[32mmethod\e[0m            show quantity grouped by method\n"
"\e[32mcli42\n"
"    \e[32mname\e[0m           username: you'll receive the email\n"
"\e[32mcli42\n"
"    \e[32memail\e[0m          email: you'll receive the username\n"
"\e[32mcli42\n"
"    \e[32mstatus\e[0m       will receive the qtty req per status\n"
"\n"
"\n"
"\e[1mTYPICAL STARTUP\e[0m\n"
"In order to utilize cli42, you will need to first have included some data in the server\n"
"If you haven’t already, do some POST through Insomnia or Postman with values like below on Header:\n"

"    \e[7mname \e[32musername\e[0m\n"
"    \e[7memail \e[32mmail@mail.com\e[0m\n"
"    \e[7mpassword \e[32mpassword\e[0m\n"

"\n";

typedef struct	s_log_db
{
	sqlite3	*db;
	char *zErrMsg;
	int rc;
}				t_log_db;

int cli(int argc, const char **argv);
void init_log_db(t_log_db *log_db);





#endif /* cli_h */
