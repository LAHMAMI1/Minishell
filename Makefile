# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: olahmami <olahmami@student.1337.ma>        +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/08/20 13:32:23 by fdiraa            #+#    #+#              #
#    Updated: 2023/08/24 13:02:01 by olahmami         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

.PHONY = all clean fclean re

NAME = minishell

# CFLAGS += -fsanitize=address 
CFLAGS += -Wall -Wextra -Werror -g3

CC = cc

PAR =	parser/parser.c parser/lexer.c parser/debug.c parser/expander.c parser/field_splitting.c parser/util.c \
		parser/parser_util.c parser/file_name_expander.c parser/env.c parser/redirections.c parser/signals.c \
		parser/get_word.c parser/ifs_delimiter_util.c parser/remove_expand_quotes.c parser/ifs_expander.c \
		parser/split_word_to_nodes.c parser/open_close_files.c parser/free_cmd_file.c \

BUILT = builtin/builtin.c builtin/echo.c builtin/export.c builtin/unset.c builtin/env.c builtin/pwd.c \
		builtin/exit.c builtin/cd.c builtin/export_errors_handler.c builtin/export_replace.c \

EXEC = executor/executor.c executor/executor_utils.c executor/global_executor.c executor/executor_init.c \
	   executor/pipe_fork.c

SRC = minishell.c $(PAR) $(BUILT) $(EXEC)
OBJS = ${SRC:%.c=%.o}

all : ${NAME}

${NAME} : ${OBJS}
	cd libft && make && make bonus && cd .. 
	$(CC) $(CFLAGS) -o ${NAME} ${OBJS} libft/libft.a  -I ~/readline-8.2 -L ~/readline-8.2 -lreadline -lcurses

clean:
	rm -rf ${OBJS}	

fclean: clean
	cd libft && make fclean && cd ..
	rm -f ${NAME}   

re: fclean all
