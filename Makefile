# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:49:11 by wcapt             #+#    #+#              #
#    Updated: 2025/08/26 14:28:57 by wcapt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Nom des exécutables
NAME = philo

# Compilateur et flags
CC = cc
CFLAGS = -Wall -Wextra -Werror -g

# Dossiers
SRC_DIR	= src
LIBFT_DIR = libft
LIBFT = $(LIBFT_DIR)/libft.a

# Fichiers sources
SRC = $(SRC_DIR)/main.c $(SRC_DIR)/parse.c $(SRC_DIR)/init.c \
		$(SRC_DIR)/free_all.c $(SRC_DIR)/setup_philo.c $(SRC_DIR)/utils.c \


# Fichiers objets
OBJ = $(SRC:.c=.o)

# Dépendances
all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR)

$(NAME): $(OBJ) $(LIBFT)
	@$(CC) $(CFLAGS) $(OBJ) $(LIBFT) -o $(NAME)
	@echo "\033[32m     ____  __    _ __                       __                  \033[0m"
	@echo "\033[32m    / __ \/ /_  (_) /___  _________  ____  / /_  ___  __________\033[0m"
	@echo "\033[32m   / /_/ / __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/\033[0m"
	@echo "\033[32m  / ____/ / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) \033[0m"
	@echo "\033[32m /_/   /_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  \033[0m"
	@echo "\033[32m                                 /_/                            \033[0m"
	@echo "\033[32m philo compiled successfully!\033[0m"                                                

$(SRC_DIR)/%.o: $(SRC_DIR)/%.c
	@$(CC) $(CFLAGS) -c $< -o $@

clean:
	@rm -f $(OBJ)
	@$(MAKE) -C $(LIBFT_DIR) clean
	@echo "\033[33m Object files removed!\033[0m"

fclean: clean
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFT_DIR) fclean
	@echo "\033[31m  Executable removed!\033[0m"

re: fclean all