# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: wcapt < wcapt@student.42lausanne.ch >      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2025/03/18 11:49:11 by wcapt             #+#    #+#              #
#    Updated: 2025/09/05 19:23:19 by wcapt            ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

# Program name
NAME        = philo

# Directories
SRCDIR      = src
OBJDIR      = obj
INCDIR      = include
LIBFTDIR    = libft

# Compiler and flags
CC          = cc
CFLAGS      = -Wall -Wextra -Werror -g3
THREADFLAGS = -pthread
CFLAGS     += $(THREADFLAGS)

# Include paths
CPPFLAGS    = -I$(INCDIR) -I$(LIBFTDIR)/include

# Linker flags & libs
LDFLAGS     = -L$(LIBFTDIR)
LDLIBS      = -lft $(THREADFLAGS)

# Colors for output
RED =    \033[0;31m
GREEN =  \033[0;32m
YELLOW = \033[0;33m
BLUE =   \033[0;34m
PURPLE = \033[0;35m
CYAN =   \033[0;36m
WHITE =  \033[0;37m
RESET =  \033[0m

# Files in SRCS
SRCS =  $(SRCDIR)/main.c \
		$(SRCDIR)/parse.c \
		$(SRCDIR)/init.c \
		$(SRCDIR)/free_all.c \
		$(SRCDIR)/utils.c \
		$(SRCDIR)/simulation.c \
		$(SRCDIR)/time.c \
		$(SRCDIR)/action.c

# Object files (préserve l'arborescence sous src/)
OBJS = $(SRCS:$(SRCDIR)/%.c=$(OBJDIR)/%.o)

# Libft
LIBFT = $(LIBFTDIR)/libft.a

# Default rule
all: $(NAME)

# Main target
$(NAME): $(LIBFT) $(OBJS)
	@echo "$(CYAN)Linking $(NAME)...$(RESET)"
	@$(CC) $(CFLAGS) $(LDFLAGS) $(OBJS) -o $(NAME) $(LDLIBS)
	@echo "\033[36m     ____  __    _ __                       __                  \033[0m"
	@echo "\033[36m    / __ \/ /_  (_) /___  _________  ____  / /_  ___  __________\033[0m"
	@echo "\033[36m   / /_/ / __ \/ / / __ \/ ___/ __ \/ __ \/ __ \/ _ \/ ___/ ___/\033[0m"
	@echo "\033[36m  / ____/ / / / / / /_/ (__  ) /_/ / /_/ / / / /  __/ /  (__  ) \033[0m"
	@echo "\033[36m /_/   /_/ /_/_/_/\____/____/\____/ .___/_/ /_/\___/_/  /____/  \033[0m"
	@echo "\033[36m                                 /_/                            \033[0m"
	@echo "$(GREEN)✅ $(NAME) compiled successfully!$(RESET)"

# Build libft
$(LIBFT):
	@echo "$(PURPLE)Compiling libft...$(RESET)"
	@$(MAKE) -C $(LIBFTDIR) --no-print-directory
	@echo "$(GREEN)✅ libft compiled!$(RESET)"

# Compile object files with automatic directory creation
$(OBJDIR)/%.o: $(SRCDIR)/%.c
	@mkdir -p $(dir $@)
	@echo "$(YELLOW)Compiling $<...$(RESET)"
	@$(CC) $(CFLAGS) $(CPPFLAGS) -c $< -o $@

# Clean object files
clean:
	@echo "$(RED)Cleaning object files...$(RESET)"
	@rm -rf $(OBJDIR)
	@$(MAKE) -C $(LIBFTDIR) clean --no-print-directory
	@echo "$(GREEN)✅ Object files cleaned!$(RESET)"

# Clean everything
fclean: clean
	@echo "$(RED)Cleaning executable...$(RESET)"
	@rm -f $(NAME)
	@$(MAKE) -C $(LIBFTDIR) fclean --no-print-directory
	@echo "$(GREEN)✅ Everything cleaned!$(RESET)"

# Rebuild everything
re: fclean all

# Debug build (sanitizer + define DEBUG)
debug: CFLAGS += -fsanitize=address -DDEBUG
debug: $(NAME)
	@echo "$(BLUE)✅ Debug version compiled!$(RESET)"

# Norminette
norm:
	@echo "$(PURPLE)Checking norminette...$(RESET)"
	@norminette $(SRCDIR) $(INCDIR) $(LIBFTDIR) 2>/dev/null || echo "$(YELLOW)norminette not found or errors detected$(RESET)"

.PHONY: all clean fclean re debug norm
