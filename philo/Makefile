CC = gcc
CFLAGS = -Wall -Wextra -Werror #-fsanitize=thread -g
CFILES = main.c \
			helper_fct.c \
			parsing.c \
			threads.c \
			mutex_fct.c \
			time_utils.c \
			utils.c
OBJ = $(CFILES:.c=.o)
NAME = philo

all: $(NAME)

t: $(NAME) clean

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) $(OBJ) -o $(NAME)

git:
	git add .
	git commit -m "make commit"

clean:
	rm $(OBJ)

fclean: clean
	rm $(NAME)

re: fclean $(NAME)
