/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mini.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:38:44 by ddyankov          #+#    #+#             */
/*   Updated: 2023/08/01 11:12:55 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINI_H
# define MINI_H

# include "./libft/libft.h"
# include <dirent.h>
# include <errno.h>
# include <fcntl.h>
# include <readline/history.h>
# include <readline/readline.h>
# include <signal.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <sys/ioctl.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <unistd.h>

typedef struct s_mini
{
	char			*input;
	char			**args;
	int				argc;
	int				*space_flag;
	int				space_or_not;
	int				*pipe_fds;
	char			**env;
	char			*value;
	int				input_fd;
	int				output_fd;
	int				append_fd;
	int				stdin_copy;
	int				stdout_copy;
	int				index;
	int				exit_flag;
	int				flag_for_pair;
	int				i;
	int				export_sw;
	int				count;
	char			**heredoc;
	char			**commands;
	int				num_commands;
	int				exit_value;
	int				count_heredoc;
	int				here;
	char			**hdoc_output;
	char			**exec_arr;
	int				red_left;
	pid_t			*pid_fork;
	int				result;
	int				fd;
	int				output_len;
	int				redirection_count;
	int				plus;
	char			*name;
	int				not_valid;
	int				is_redirection;

	int				xx;
	int				swit;
	char			*envvv;
	int				j;
	int				env_index;
	int				sw_dollar;
	char			*str_to_look;
	int				a;
	char			*new_str;
	int				in;
	int				abc;
	int				z;
}					t_mini;

extern unsigned int	g_exit_status;

/* main utils */
void				ft_handle_input(t_mini *mini);
void				ft_copy_envp(t_mini *mini);
void				ft_check_status(t_mini *mini, int status);

// builtins_echo.c
void				ft_handle_echo(t_mini *mini);
void				ft_echo(t_mini *mini, char **args, int i);
void				ft_echo_double(t_mini *mini, char *args, int index);
void				ft_echo_single(t_mini *mini, char *args, int index);
void				ft_echo_unclosed(t_mini *mini, char *args, int index);
int					ft_check_n(t_mini *mini, int j);

// builtins_echo2.c
void				ft_echo_env(t_mini *mini, char *args);
int					ft_split_double(t_mini *mini, char *args, int i);
int					ft_envval_doublequote(t_mini *mini, char *args, char *str,
						int i);
int					ft_split_unclosed(t_mini *mini, char *args, int i);
int					ft_envval_unclosed(t_mini *mini, char *args, char *str,
						int i);

// builtins_echo3.c
int					ft_check_for_end(t_mini *mini, char *str, int i);
int					ft_echo_unclosed_loop(t_mini *mini, char *args, int i);
int					ft_check_folder(t_mini *mini);

// builtins_main.c
void				ft_execute_built_ins(t_mini *mini, char *input);
int					ft_is_builtin(t_mini *mini, char *command);

// builtins.c
void				ft_show_directory(t_mini *mini);
void				ft_show_environment(t_mini *mini);

// builtins_export_unset.c
char				**ft_set_env_var(char *name, char *value, char **env,
						t_mini *mini);
char				**ft_unset_environment_variable(t_mini *mini);
char				**ft_modified_env(t_mini *mini, int count);
void				ft_handle_export(t_mini *mini);

// builtins_export_unset_utils.c
int					ft_name(t_mini *mini);
int					ft_value(t_mini *mini);
int					ft_env(char **env, char **new_env);

// builtins_export_unset_utils2.c
void				ft_check_chars(t_mini *mini, int i);
char				*ft_put_value(char *env_val, char *value,
						char *final_value);
void				ft_final_value(t_mini *mini, char *value);
int					ft_value_return(t_mini *mini, int i);

// cd.c
void				ft_change_directory(t_mini *mini);
char				*ft_get_current_path(t_mini *mini);
int					ft_check_arguments_num(t_mini *mini, char *current_path);

// cd_utils.c
void				ft_set_pwd(t_mini *mini);

// command_check.c
int					ft_check_if_command(t_mini *mini);
int					ft_check_if_external(t_mini *mini);
int					ft_check_if_access(t_mini *mini, int i, char **dirs,
						char **args);

// count_input_arguments.c
void				ft_count_if_space(t_mini *mini);
void				ft_count_if_single_quote(t_mini *mini);
void				ft_count_if_double_quote(t_mini *mini);
void				ft_count_if_redirections(t_mini *mini, char c);
void				ft_count_if_pipes(t_mini *mini);

// execute_external.c
int					ft_change_value(t_mini *mini);
void				ft_exit_if_no_path(t_mini *mini);
void				ft_search_and_execute(t_mini *mini, int sw);
int					ft_check_access_for_external(t_mini *mini, int i,
						char **dirs, char **args);
void				ft_execute_external(char *path, t_mini *mini, char **args,
						char **dirs);

// exit.c
void				ft_exit(char *input, t_mini *mini);

// expand.c
int					ft_expand(t_mini *mini);
int					ft_expand_str(t_mini *mini, int i);

// new_args.c
char				*ft_get_new_str(t_mini *mini);
//  free.c
void				ft_free_input(t_mini *mini);
void				ft_free_result_commands(t_mini *mini);
void				ft_free_when_forked(t_mini *mini);
void				ft_free_malloc(t_mini *mini);
void				ft_free_env_input(t_mini *mini);

// modifying_quotes.c
void				ft_init_struct(t_mini *mini);
void				ft_skip_spaces(t_mini *mini, char *str);
void				ft_reset_flag(t_mini *mini);
int					ft_check_if_num(t_mini *mini, char *str);

// pipe_commands.c
void				ft_execute_built_in_command(t_mini *mini, char **args);

// pipe_split.c
void				ft_split_into_commands(t_mini *mini);
void				ft_help_split_commands(t_mini *mini, int i, int index,
						char *command);

// pipe_utils.c
void				ft_create_pipes(t_mini *mini, int *pipe_fds);
void				ft_close_pipes(int num_commands, int *pipe_fds);
void				ft_output(t_mini *mini, int i, int num_commands,
						int *pipe_fds);
void				ft_input(t_mini *mini, int i, int *pipe_fds);
void				ft_dup_child(t_mini *mini, int i, int num_commands,
						int *pipe_fds);

// pipe.c
int					ft_execute_pipes(t_mini *mini);
void				ft_fork_for_commands(t_mini *mini, int *pipe_fds);
void				ft_fork_for_commands_extension(t_mini *mini, int i,
						int *pipe_fds);
void				ft_wait_for_processes(t_mini *mini, int num_commands);

// redirections_double_left_utils.c
int					ft_read_input_redirection(t_mini *mini, int i);

//  redirections_main.c
int					ft_check_for_redirection(t_mini *mini);
char				*ft_get_path(t_mini *mini);
void				ft_fork_redirections(t_mini *mini);
void				ft_count_double_left(t_mini *mini);
void				ft_input_fd(t_mini *mini);

// redirections_handle_fds.c
void				ft_apply_input_redirections(t_mini *mini);
void				ft_restore_and_close_fds(t_mini *mini);
int					ft_redirect_right_check(t_mini *mini);

// signals.c
void				sigint_handler(int sig);
void				handle_sigquit(int sig);
void				ft_ctrl_d(t_mini *mini);
void				sigint_heredoc(int sig);

// split_input_for_quotes.c
void				ft_split_double_quotes(t_mini *mini);
void				ft_split_single_quotes(t_mini *mini);
void				ft_single_and_double_extension(t_mini *mini, int j, int x);

// split_input_for_space_pipes_red.c
void				ft_split_space(t_mini *mini);
int					ft_put_in_args_extension(t_mini *mini);
int					ft_split_redirections(t_mini *mini, char c);
int					ft_split_pipes(t_mini *mini);

// split_input_main.c
int					ft_split_input(t_mini *mini);
void				ft_count_arguments(t_mini *mini);
int					ft_handle_spaceflag(t_mini *mini, int j);

// split_input_utils.c
int					ft_swap_arguments(t_mini *mini);
void				ft_redirections_change_position(t_mini *mini, int sw);
int					ft_look_for_quote(t_mini *mini, char *str, int i);
void				ft_look_for_pair(t_mini *mini);
int					ft_look_for_pair_in_pair(t_mini *mini);

// utils.c
int					ft_strcmp_with_quotes(t_mini *mini, char *str,
						char *builtin);
int					ft_strcmp_with_quotes_extension(t_mini *mini, char *str,
						char *builtin, int i);
void				ft_write_without_quotes(t_mini *mini, char *str);
int					ft_delete_quotes_for_str(t_mini *mini, int i);
int					ft_delete_quotes(t_mini *mini);
void				ft_command_not_found(t_mini *mini, int sw, int i);
void				ft_write_space(t_mini *mini, int index);
void				ft_check_path(t_mini *mini, char *path_env, int sw);
void				ft_write_space(t_mini *mini, int index);
void				ft_fork_error(void);
void				ft_execve_error(t_mini *mini);
void				ft_no_path(t_mini *mini);
void				ft_not_valid(t_mini *mini);
void				ft_pwd(t_mini *mini);
int					ft_check_multiple_redirections(t_mini *mini);
char				*ft_new_str(t_mini *mini, char *delim);
int					ft_swit(t_mini *mini);
int					ft_x(t_mini *mini);
void				ft_fork_heredoc(t_mini *mini, char *inp_line, char *delim);
char				*ft_replace_line(char *s, t_mini *mini);
int					ft_valid_or_not(t_mini *mini, int i);
void				ft_yes_directory(t_mini *mini);
int					ft_question(t_mini *mini);
void				ft_allocate_and_initiate(t_mini *mini);
void				ft_free_heredoc(t_mini *mini);
int					ft_exit_out(t_mini *mini);
char				*ft_remove_quotes(t_mini *mini, char *str);
void				ft_write_quotes(t_mini *mini);
void				ft_skip_dollar(t_mini *mini);
int					ft_unexpected(t_mini *mini);
int					ft_check_mini_arg(t_mini *mini, char *s);
int					ft_loop_more_strings(t_mini *mini);
#endif
