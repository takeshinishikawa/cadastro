# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/26 15:13:52 by rtakeshi          #+#    #+#              #
#    Updated: 2022/02/27 21:49:25 by rtakeshi         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.DEFAULT_GOAL:=  all
NAME	=	cli42

CFLAGS = -W -Wall -g -DMG_ENABLE_LINES=1 -pthread


RM		=	rm -rf
OBJ_DIR	=	obj

DEP			=	dependencies
INC_DIR 	= 	inc
INC			= -I inc -I dependencies/libft/

LIB			= -L dependencies/libft/ -l ft

SRC_DIR	=	src
SRC 	= $(addprefix $(SRC_DIR)/, cli.c sqlite3.c log_create_table.c)
OBJ		=	$(SRC:$(SRC_DIR)/%.c=$(OBJ_DIR)/%.o)

all:			$(NAME)


$(NAME):		$(DEP) $(OBJ_DIR) $(OBJ)
				gcc $(CFLAGS) $(OBJ) $(LIB) $(INC) -o $(NAME) -ldl
				sudo mv $(NAME) /usr/local/bin

$(OBJ_DIR)/%.o:	$(SRC_DIR)/%.c
				gcc $(LIB) $(INC) -c $< -ldl -o $@

$(OBJ_DIR):
				mkdir $(OBJ_DIR)

$(DEP):
				make -C $(DEP)/libft

run:			$(NAME)
				./${NAME}

clean:
				$(RM) $(OBJ_DIR)

fclean: 		clean
				sudo $(RM) /usr/local/bin/cli42

re:				fclean all

.PHONY:			all clean fclean re dependencies
