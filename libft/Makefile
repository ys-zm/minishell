# **************************************************************************** #
#                                                                              #
#                                                         ::::::::             #
#    Makefile                                           :+:    :+:             #
#                                                      +:+                     #
#    By: fra <fra@student.42.fr>                      +#+                      #
#                                                    +#+                       #
#    Created: 2022/10/14 18:27:31 by anonymous     #+#    #+#                  #
#    Updated: 2023/03/23 16:25:29 by fra           ########   odam.nl          #
#                                                                              #
# **************************************************************************** #

SHELL := /bin/bash

NAME := libft.a
SRC_DIR := sources
OBJ_DIR := objects
INCLUDE  := include

HEADERS := $(shell find $(INCLUDE) -type f -name '*.h')
SOURCES := $(shell find $(SRC_DIR) -type f -name '*.c')
OBJECTS := $(patsubst $(SRC_DIR)%,$(OBJ_DIR)%,$(SOURCES:.c=.o))

CC  := gcc
IFLAGS := -I $(INCLUDE)
CFLAGS := -Wall -Wextra -Werror
LFLAGS := -rcs

GREEN = \x1b[32;01m
RED = \x1b[31;01m
BLUE = \x1b[34;01m
RESET = \x1b[0m
YELLOW = \x1b[33;01m

all: $(NAME)

$(NAME): $(OBJ_DIR) $(OBJECTS) $(HEADERS)
	@ar $(LFLAGS) $(NAME) $(OBJECTS)
	@printf "(libft) $(YELLOW)Created archive $(NAME)$(RESET)\n"

$(OBJ_DIR):
	@mkdir -p $(OBJ_DIR)

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(IFLAGS) -c $^ -o $@
	@printf "(libft) $(BLUE)Created object $$(basename $@)$(RESET)\n"

clean:
	@for file in $(shell find $(OBJ_DIR) -type f -name '*.o'); do \
		rm -f $$file;	\
		printf "(libft) $(RED)Removed object $$(basename $$file)$(RESET)\n"; \
	done

fclean:
	@-rm -f $(NAME)
	@printf "(libft) $(RED)Removed archive $(NAME)$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
