NAME = philo
CC = cc
CFLAGS = -g -Werror -Wall -Wextra -pthread

OBJ_PATH = obj/

SRC =	about_time.c \
		death.c \
		exit.c \
		init.c \
		is_input_valid.c \
		main.c \
		output.c \
		philosopher.c

OBJ = $(SRC:.c=.o)
OBJS = $(addprefix $(OBJ_PATH), $(OBJ))

INC = -I ./philo.h

all: $(NAME)

$(NAME): $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) -o $@
	
$(OBJ_PATH)%.o: %.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

clean:
	@rm -rf $(OBJ_PATH)
	@echo -clean is ok-

fclean:
	@rm -rf $(OBJ_PATH)
	@rm -f $(NAME)
	@echo -fclean is ok-

re: fclean all

.PHONY: all clean fclean re