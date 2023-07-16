SHELL := /bin/bash

NAME := minishell
SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
HERE_DOC_DIR := here_doc/
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := $(shell find include -type f -name '*.h')
SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))	

CC  := cc
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g3 -fsanitize=address
CFLAGS += -arch x86_64
LFLAGS := -Llibft -lft -lreadline -lhistory 

ifeq ($(shell uname -s),Darwin)			# Mac
	IFLAGS := $(IFLAGS) -I$(shell brew --prefix readline)/include
	LFLAGS := $(LFLAGS) -L$(shell brew --prefix readline)/lib
endif

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
YELLOW = \x1b[33;01m
RESET = \x1b[0m


all: $(LIBFT) $(NAME)

run: all
	@clear
	@./$(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@mkdir -p $(HERE_DOC_DIR)
	@$(CC) $(CFLAGS) $(IFLAGS) $(OBJECTS) $(LFLAGS) -o $(NAME)
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


.DEFAULT_GOAL:=all
