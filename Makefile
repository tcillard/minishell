# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: tcillard <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/03/27 05:29:43 by tcillard          #+#    #+#              #
#    Updated: 2019/05/31 18:02:48 by tcillard         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC = gcc

FLAGS = -Wall -Wextra -Werror

SRC_NAME =	main.c \
			ft_minishell.c \
			ft_exec_bin.c \
			ft_built.c \
			ft_error.c \
			ft_echo.c \
			ft_parser_arg.c \
			ft_cd.c \
			ft_env.c \
			ft_lst_env.c \
			ft_set_env.c \
			ft_unset_env.c \
			ft_signal.c \
			ft_replace_home.c \
			ft_env_base.c

OBJ_NAME = $(SRC_NAME:.c=.o)

SRC_PATH = ./src
OBJ_PATH = ./obj

LIBFT = -L ./libft  -lft
INCLUDE = -I include/ -I ./libft

NAME = minishell

SRC = $(addprefix $(SRC_PATH)/,$(SRC_NAME))
OBJ = $(addprefix $(OBJ_PATH)/,$(OBJ_NAME))

all: $(NAME)

$(OBJ_PATH)/%.o: $(SRC_PATH)/%.c
	@$(CC) -c $(INCLUDE) $< -o $@
	@echo "\033[0m$< -> $@ \033[38;2;0;255;0m[ok]\033[0m"

dir:
	@-mkdir $(OBJ_PATH)

$(NAME): libft dir $(OBJ) logo
	@$(CC) $(FLAGS) $(INCLUDE) $(SRC) $(LIBFT) -o $(NAME)

libft:
	@make -C libft/

logo:
		@echo "\n"
		@echo "\033[31;3;255;255;255m                    88               88             88                       88  88 "
		@echo "\033[36;3;255;255;255m                    \"\"               \"\"             88                       88  88  "
		@echo "\033[31;3;255;255;255m                                                    88                       88  88  "
		@echo "\033[36;3;255;255;255m88,dPYba,,adPYba,   88  8b,dPPYba,   88  ,adPPYba,  88,dPPYba,    ,adPPYba,  88  88  "
		@echo "\033[31;3;255;255;255m88P'   \"88\"    \"8a  88  88P'   \`\"8a  88  I8[    \"\"  88P'    \"8a  a8P_____88  88  88 "
		@echo "\033[36;3;255;255;255m88      88      88  88  88       88  88   \`\"Y8ba,   88       88  8PP\"\"\"\"\"\"\"  88  88 "
		@echo "\033[31;3;255;255;255m88      88      88  88  88       88  88  aa    ]8I  88       88  \"8b,   ,aa  88  88  "
		@echo "\033[36;3;255;255;255m88      88      88  88  88       88  88  \`\"YbbdP\"'  88       88   \`\"Ybbd8\"'  88  88  "
		@echo "\033[37;3;255;255;255m"

clean:
	@$(MAKE) -C libft clean
	@rm -rf ./obj

fclean: clean
	@$(MAKE) -C libft/ fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re logo libft
