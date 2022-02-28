NAME =	libmongoose.a
CC =	gcc
CFLAGS =	-Wall -Wextra -Werror
INC	= mongoose.h
SRC	= mongoose.c
OBJ =	$(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
		@ar rc $(NAME) $(OBJ)
		@ranlib $(NAME)

$(OBJ): $(SRC) $(INC)
		$(CC) $(CFLAGS) -c $(SRC) $(INC)
