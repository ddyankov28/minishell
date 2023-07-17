/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:10:18 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/17 21:38:59 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

unsigned int	g_exit_status;

static void	ft_check_args(int ac, char **av)
{
	if (ac > 1)
	{
		printf("./minishell: %s: No such file or directory\n", av[1]);
		exit(1);
	}
}

int	ft_check_input(t_mini *mini, char *input)
{
	int	i;

	i = 0;
	if (ft_strcmp(input, "\"\"") == 0)
	{
		printf("'': command not found\n");
		mini->exit_value = 127;
		return (1);
	}
	else if (input[i] == ' ')
	{
		while (input[i] == ' ' && input[i])
			i++;
		if (input[i] == '\0')
			return (1);
	}
	return (0);
}

int	main(int argc, char **argv)
{
	t_mini	mini;

	ft_check_args(argc, argv);
	ft_copy_envp(&mini);
	mini.exit_value = 0;
	while (1)
	{
		signal(SIGINT, sigint_handler);
		signal(SIGQUIT, SIG_IGN);
		ft_init_struct(&mini);
		mini.input = readline("~$ ");
		ft_ctrl_d(&mini);
		if (mini.input[0] != '\0' && ft_check_input(&mini, mini.input) == 0)
		{
			ft_split_input(&mini);
			ft_handle_input(&mini);
		}
		if (ft_strlen(mini.input) > 0)
			add_history(mini.input);
		free(mini.input);
	}
	ft_free_2d_arr(mini.env);
	rl_clear_history();
	return (0);
}
