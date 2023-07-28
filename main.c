/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/26 15:10:18 by ddyankov          #+#    #+#             */
/*   Updated: 2023/07/27 19:34:46 by vstockma         ###   ########.fr       */
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

int	ft_check_inp(t_mini *mini, char *input)
{
	int	i;

	i = 0;
	while ((input[i] == '\'' || input[i] == '\"') && input[i])
		i++;
	if (input[i] == '\0')
	{
		ft_write_without_quotes(mini, input);
		printf(": command not found\n");
		mini->exit_value = 127;
		return (1);
	}
	return (0);
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
	else if (input[i] == '\'' || input[i] == '\"')
	{
		if (ft_check_inp(mini, input) == 1)
			return (1);
	}
	return (0);
}

static void	ft_increase_shllvl(t_mini *mini)
{
	char	*shlvl_value;
	char	*name;
	char	*new_shl;
	int		value;

	name = "SHLVL";
	shlvl_value = ft_get_value_from_env(mini->env, "SHLVL");
	if (!shlvl_value)
		value = 0;
	else
		value = ft_atoi(shlvl_value);
	value = value + 1;
	shlvl_value = ft_itoa(value);
	new_shl = ft_strjoin("SHLVL=", shlvl_value);
	mini->env = ft_set_env_var(name, new_shl, mini->env, mini);
	free(shlvl_value);
	free(new_shl);
}

int	main(int argc, char **argv)
{
	t_mini	mini;

	ft_check_args(argc, argv);
	ft_copy_envp(&mini);
	ft_increase_shllvl(&mini);
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
			if (ft_split_input(&mini) != 1)
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
