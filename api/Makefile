# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/05 19:39:57 by rtakeshi          #+#    #+#              #
#    Updated: 2022/02/27 22:09:52 by rtakeshi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL:= all
NAME	=	api

CFLAGS = -W -Wall -g -DMG_ENABLE_LINES=1 -pthread
ifneq ($(MBEDTLS_DIR),)
CFLAGS += -DMG_ENABLE_MBEDTLS=1 -I$(MBEDTLS_DIR)/include -I/usr/include
CFLAGS += -L$(MBEDTLS_DIR)/lib -lmbedtls -lmbedcrypto -lmbedx509
else ifneq ($(OPENSSL_DIR),)
CFLAGS += -DMG_ENABLE_OPENSSL=1 -I$(OPENSSL_DIR)/include
CFLAGS += -L$(OPENSSL_DIR)/lib -lssl -lcrypto
endif

RM		=	rm -rf
OBJ_DIR	=	obj

DEP			=	dependencies
INC_DIR 	= 	inc
INC			= -I inc -I dependencies/libft/ -I dependencies/mongoose

LIB			= -L dependencies/libft/ -l ft -L dependencies/mongoose -l mongoose

SRC_DIR	=	src
SRC 	= $(addprefix $(SRC_DIR)/, api.c sqlite3.c create_table.c create_user.c get_user.c \
		update_password.c delete_user.c log_create_table.c log_insert.c api_utils.c)

OBJ		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all:			$(NAME)

$(NAME):		$(DEP) $(OBJ_DIR) $(OBJ)
				gcc $(CFLAGS) $(OBJ) $(LIB) $(INC) -o $(NAME) -ldl

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				gcc $(LIB) $(INC) -c $< -ldl -o $@

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(DEP):
				make -C $(DEP)/libft
				make -C $(DEP)/mongoose

run:			$(NAME)
				./${NAME}

clean:
				$(RM) $(OBJ_DIR)

fclean: 		clean
				$(RM) $(NAME)

re:				fclean all

.PHONY:			all clean fclean re dependencies
