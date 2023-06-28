SHELL := /bin/bash

NAME := minishell
SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
HERE_DOC_DIR := here_doc/
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := include/minishell.h
#$(shell find include -type f -name '*.h')
SOURCES = sources/builtins/cd_utils_1.c \
			sources/builtins/cd_utils_2.c \
			sources/builtins/export_utils_1.c \
			sources/builtins/export_utils_2.c \
			sources/builtins/ft_cd.c \
			sources/builtins/ft_echo.c \
			sources/builtins/ft_env.c \
			sources/builtins/ft_exit.c \
			sources/builtins/ft_export.c \
			sources/builtins/ft_pwd.c \
			sources/builtins/ft_unset.c \
			sources/builtins/utils.c \
			sources/checker/check_char.c \
			sources/checker/check_sintax.c \
			sources/checker/check_string.c \
			sources/env/env_parsing.c \
			sources/env/utils.c \
			sources/error_handling/error.c \
			sources/error_handling/free.c \
			sources/exec/access.c \
			sources/exec/access_utils.c \
			sources/exec/builtin_exec.c \
			sources/exec/child_process.c \
			sources/exec/exec.c \
			sources/exec/init_exec.c \
			sources/exec/init_paths.c \
			sources/exec/multiple_cmds.c \
			sources/exec/path_utils.c \
			sources/exec/redirections.c \
			sources/exec/shlvl.c \
			sources/lexer/builder.c \
			sources/lexer/lexer.c \
			sources/lexer/tokenizer.c \
			sources/main/main.c \
			sources/parser/cmd.c \
			sources/parser/expander.c \
			sources/parser/here_doc_handle.c \
			sources/parser/here_doc_write.c \
			sources/parser/read_input.c \
			sources/utils/tools.c
#$(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))	

CC  := cc
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include
CFLAGS = -Wall -Wextra -Werror
# CFLAGS += -g3 -fsanitize=address
# CFLAGS += -arch x86_64
LFLAGS := -Llibft -lft -lreadline -lhistory 

ifeq ($(shell uname -s),Darwin)			# Mac
	IFLAGS := $(IFLAGS) -I$(shell brew --prefix readline)/include
	LFLAGS := $(LFLAGS) -L$(shell brew --prefix readline)/lib
endif

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(LIBFT) $(NAME)

run: all
	./$(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_DIR) --quiet

$(NAME): $(OBJ_DIR) $(OBJECTS)
	@mkdir -p $(HERE_DOC_DIR)
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


.DEFAULT_GOAL:=all
