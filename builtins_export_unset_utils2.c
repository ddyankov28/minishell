/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_export_unset_utils2.c                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ddyankov <ddyankov@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/18 16:49:08 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/27 16:44:39 by ddyankov         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

void	ft_check_chars(t_mini *mini, int i)
{
	if ((mini->args[1][i] >= 33 && mini->args[1][i] <= 42)
		|| (mini->args[1][i] >= 44 && mini->args[1][i] <= 47)
		|| (mini->args[1][i] >= 58 && mini->args[1][i] <= 60)
		|| (mini->args[1][i] >= 62 && mini->args[1][i] <= 64)
		|| (mini->args[1][i] >= 91 && mini->args[1][i] <= 94)
		|| mini->args[1][i] == 96
		|| (mini->args[1][i] >= 123 && mini->args[1][i] <= 126))
	{
		mini->export_sw++;
		mini->not_valid = 1;
	}
}

char	*ft_put_value(char *env_val, char *value, char *final_value)
{
	int	i;
	int	j;
	int	x;

	x = 0;
	j = 0;
	i = 0;
	while (value[i])
	{
		if (value[i] == '+' && value[i + 1] == '=')
		{
			i++;
			while (value[i] == '=' && value[i])
				final_value[j++] = value[i++];
			if (env_val != NULL)
			{
				while (env_val[x])
					final_value[j++] = env_val[x++];
			}
		}
		final_value[j++] = value[i++];
	}
	final_value[j] = '\0';
	return (final_value);
}

void	ft_final_value(t_mini *mini, char *value)
{
	char	*final_value;
	char	*env_val;

	env_val = ft_get_value_from_env(mini->env, mini->name);
	final_value = malloc(ft_strlen(value) + ft_strlen(env_val) + 1);
	if (!final_value)
	{
		free(final_value);
		ft_free_malloc(mini);
	}
	final_value = ft_put_value(env_val, value, final_value);
	free(mini->value);
	mini->value = ft_strdup(final_value);
	free(final_value);
}

int	ft_value_return(t_mini *mini, int i)
{
	if (mini->args[i + 1] == NULL)
	{
		ft_final_value(mini, mini->value);
		return (0);
	}
	return (1);
}

void	sigint_heredoc(int sig)
{
	(void)sig;
	ioctl(0, TIOCSTI, "\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	g_exit_status = 130;
}
