SHELL := /bin/bash

NAME := minishell
SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := $(shell find include -type f -name '*.h')
SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))	

CC  := gcc
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include
CFLAGS := -Wall -Wextra -Werror -g3 #-fsanitize=address
LFLAGS := -Llibft -lft -lreadline -lhistory

ifeq ($(shell uname -s),Darwin)			# Mac
	IFLAGS := $(IFLAGS) -I$(shell brew --prefix readline)/include
	LFLAGS := $(LFLAGS) -L$(shell brew --prefix readline)/lib 
#-lreadline -lhistory
endif

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(LIBFT) $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

#su Linux invertito l'ordine di $(OBJECTS) e $(LFLAGS)
$(NAME): $(OBJ_DIR) $(OBJECTS)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJECTS) $(LFLAGS) -o $(NAME)
	@clear
	@printf "(minishell) $(GREEN)Created program $(NAME)$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c $(HEADERS)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $< -o $@
	@printf "(minishell) $(BLUE)Created object $$(basename $@)$(RESET)\n"

clean:
	@$(MAKE) clean -C $(LIBFT_DIR) --quiet
	@for file in $(OBJECTS); do \
		rm -f $$file;	\
		printf "(minishell) $(RED)Removed object $$(basename $$file)$(RESET)\n"; \
	done

fclean: clean
	@$(MAKE) fclean -C $(LIBFT_DIR) --quiet
	@-rm -f $(NAME)
	@printf "(minishell) $(RED)Removed executable $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all, clean, fclean, re
