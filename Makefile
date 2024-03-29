# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: eros-gir <eros-gir@student.42barcel>       +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/08/02 14:48:15 by eros-gir          #+#    #+#              #
#    Updated: 2023/09/08 19:55:34 by eros-gir         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

C_GREEN=\033[0;32m
C_RED=\033[0;31m
C_YELLOW=\033[0;33m
C_END=\033[0m

NAME = minishell

SRC = ./src/ms_main.c  \
	./src/ms_mainhelpers.c \
	./src/ms_signals.c \
	./src/parser/ms_parser.c \
	./src/parser/ms_parser2.c \
	./src/executions/ms_execmd.c \
	./src/executions/ms_execpath.c \
	./src/executions/ms_pipe.c \
	./src/executions/ms_exehelpers.c \
	./src/redirections/ms_redirections.c \
	./src/redirections/ms_redirections2.c \
	./src/redirections/ms_redirections3.c \
	./src/redirections/ms_heredoc.c \
	./src/redirections/ms_heredochelpers.c \
	./src/redirections/ms_redirhelpers.c \
	./src/parser/env_parser/ms_env_parser.c \
	./src/tokenizer/ms_tokenizer.c \
	./src/tokenizer/ms_tokenizer_2.c \
	./src/built_ins/ms_built_ins.c \
	./src/built_ins/execs/ms_exec_exit.c \
	./src/built_ins/execs/ms_exec_exit_2.c \
	./src/built_ins/execs/ms_exec_echo.c  \
	./src/built_ins/execs/ms_exec_env.c \
	./src/built_ins/execs/ms_exec_pwd.c \
	./src/built_ins/execs/ms_exec_cd.c \
	./src/built_ins/execs/ms_exec_cd_2.c \
	./src/built_ins/execs/ms_exec_unset.c \
	./src/built_ins/execs/ms_exec_export.c \
	./src/expander/ms_expander.c \
	./src/utils/ms_utils.c ./src/helpers/ms_helpers.c \
	./src/validations/ms_validations.c \
	./src/validations/ms_validations_2.c \
	./src/destroyer/ms_destroyer.c \
	./src/errors/ms_errors.c \
	./src/errors/ms_errors2.c \

HDR = ./incl/mslib.h ./libft/libft.h

LIBFTDIR = ./libft/

OBJ = $(SRC:.c=.o)

GC = gcc 
CFLAGS = -g -Wall -Wextra -Werror
LFLAGS = -L $(LIBFTDIR) -lft -lreadline
LDFLAGS		= -L/Users/$(USER)/.brew/opt/readline/lib
CPPFLAGS	= -I/Users/$(USER)/.brew/opt/readline/include

%.o: %.c $(HDR)
	@$(GC) $(CFLAGS) $(CPPFLAGS) -o $@ -c $<

all: make_lib $(NAME)

make_lib:
	@echo "$(C_YELLOW)make libft...$(C_END)"
	make -C $(LIBFTDIR)

$(NAME): $(OBJ) $(HDR) libft/libft.a
	@echo "$(C_YELLOW)make minishell...$(C_END)"
	$(GC) $(CFLAGS) $(LDFLAGS) -o $(NAME) $(OBJ) $(LFLAGS)
	@echo "$(C_GREEN)FINISHED!$(C_END)"

clean:
	@echo "$(C_RED)cleaning *.o$(C_END)"
	make clean -s -C $(LIBFTDIR)
	rm -f $(OBJ)
	@echo "$(C_GREEN)FINISHED!$(C_END)"

fclean: clean
	@echo "$(C_RED)cleaning executable$(C_END)"
	make fclean -s -C $(LIBFTDIR)
	rm -f $(NAME)
	@echo "$(C_GREEN)FINISHED!$(C_END)"

re: fclean all
	@echo "$(C_GREEN)Recompiled!$(C_END)"