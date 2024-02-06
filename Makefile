NAME = philo_bonus

CC = cc -Wall -Wextra -Werror -g -lpthread -pthread

SRC =	death_bonus.c	ft_atoi_bonus.c	initialize_bonus.c	main.c \
		print_bonus.c	process.c	routine_bonus.c	semaphores.c	\
		time_bonus.c 	utils_bonus.c	main_process_bonus.c	\
		../philo/ft_strlen.c 

OBJ = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(OBJ)
	@$(CC) $(OBJ) -o $(NAME)
	@echo "Compiled "$(NAME)" successfully!"

%.o: %.c
	@$(CC) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@echo "Cleaned objects successfully!"

fclean: clean
	@rm -f $(NAME)
	@echo "Cleaned "$(NAME)" successfully!"

re: fclean all

.PHONY: all clean fclean re
