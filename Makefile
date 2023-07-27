# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/26 15:22:07 by ddyankov          #+#    #+#              #
#    Updated: 2023/07/27 16:36:51 by ddyankov         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = minishell

SRC = main.c main_utils.c\
	builtins_echo.c builtins_echo2.c builtins_echo3.c\
	builtins_main.c builtins.c builtins_export_unset.c builtins_export_unset_utils.c\
	builtins_export_unset_utils2.c\
	exit.c cd.c cd_utils.c\
	count_input_arguments.c command_check.c\
	pipe.c pipe_utils.c pipe_split.c pipe_commands.c\
	redirections_main.c redirections_main_utils.c\
	redirections_double_left_utils.c redirections_handle_fds.c\
	execute_external.c redirections_fork.c\
	split_input_main.c split_input_for_space_pipes_red.c split_input_for_quotes.c\
	split_input_utils.c\
	free.c\
	modifying_quotes.c\
	utils.c utils2.c utils3.c\
	signals.c\
	expand.c new_args.c\

OBJS = $(SRC:.c=.o)

CFLAGS = -Wall -Werror -Wextra -g

LIBFT = libft/libft.a

all: $(NAME)

$(NAME): $(OBJS) $(LIBFT)
	@cc $(CFLAGS) $(OBJS) $(LIBFT) -lreadline -o $(NAME)
$(LIBFT):
	@make -C libft -s
clean:
	@rm -f $(OBJS)
	@make clean -C libft
fclean: clean
	@rm -f $(NAME)
	@make fclean -C libft
re: fclean all

.PHONY:		all clean fclean re