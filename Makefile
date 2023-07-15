SHELL := /bin/bash

NAME := minishell
SRC_DIR := sources
OBJ_DIR := objects
LIBFT_DIR := libft
HERE_DOC_DIR := here_doc/
LIBFT := $(LIBFT_DIR)/libft.a
HEADERS := $(shell find include -type f -name '*.h')
# include/main/main.h \
# include/utils/utils.h \
# include/env/env.h \
# include/builtins/builtins.h \
# include/here_doc/here_doc.h \
# include/error_handling/error_handling.h \
# include/minishell/minishell.h \
# include/minishell/enum.h \
# include/exec/exec.h \
# include/checker/checker.h \
# include/parser/parser.h \
# include/lexer/lexer.h
SOURCES = $(shell find $(SRC_DIR) -type f -name '*.c')
# sources/builtins/cd_utils_1.c \
# sources/builtins/cd_utils_2.c \
# sources/builtins/export_utils_1.c \
# sources/builtins/export_utils_2.c \
# sources/builtins/ft_cd.c \
# sources/builtins/ft_echo.c \
# sources/builtins/ft_env.c \
# sources/builtins/ft_exit.c \
# sources/builtins/ft_export.c \
# sources/builtins/ft_pwd.c \
# sources/builtins/ft_unset.c \
# sources/builtins/utils.c \
# sources/checker/check_chars.c \
# sources/checker/check_sintax.c \
# sources/checker/check_valid.c \
# sources/env/env_parsing.c \
# sources/env/utils.c \
# sources/error_handling/error.c \
# sources/error_handling/free.c \
# sources/exec/access.c \
# sources/exec/access_utils.c \
# sources/exec/builtin_exec.c \
# sources/exec/child_process.c \
# sources/exec/exec.c \
# sources/exec/init_exec.c \
# sources/exec/init_paths.c \
# sources/exec/multiple_cmds.c \
# sources/exec/path_utils.c \
# sources/exec/redirections.c \
# sources/exec/shlvl.c \
# sources/here_doc/here_doc_handle.c \
# sources/here_doc/here_doc_write.c \
# sources/lexer/builder.c \
# sources/lexer/lexer.c \
# sources/lexer/tokenizer.c \
# sources/main/main.c \
# sources/main/signals.c \
# sources/parser/command.c \
# sources/parser/expander.c \
# sources/parser/parser.c \
# sources/utils/utils.c
OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))	

CC  := cc
IFLAGS := -Iinclude -I$(LIBFT_DIR)/include
CFLAGS = -Wall -Wextra -Werror
CFLAGS += -g3 -fsanitize=address
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
	./$(NAME)

git: 
# fclean
# @git push

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
