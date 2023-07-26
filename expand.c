/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:38:55 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/26 11:45:37 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char	*ft_get_new_str(t_mini *mini)
{
	char	*new_str;
	static int		env;
	int		j;
	int		a;
	char	*str_to_look;
	int		i;
	int		sw;
	
	sw = 0;
	new_str = malloc(1024);
	str_to_look =  ft_calloc(1024, 1);
	if (!new_str)
	{
		free(new_str);
		ft_free_malloc(mini);
	}
	i = 0;
	j = 0;
	while (mini->args[mini->xx])
	{
		a = 0;
		if (mini->args[mini->xx][j] == '\"')
		{
			ft_delete_quotes_for_str(mini, mini->xx);
			sw = 2;
		}
		else if (mini->args[mini->xx][j] == '\'')
		{
			ft_delete_quotes_for_str(mini, mini->xx);
			sw = 1;
		}
		if (mini->args[mini->xx][j] == '$' && (sw == 0 || sw == 2)
			&& mini->args[mini->xx][j + 1] != '\0')
		{
			j++;
			env = 0;
			while (mini->args[mini->xx][j] != '$' && mini->args[mini->xx][j]
				&& mini->args[mini->xx][j] != ' ')
			{
				str_to_look[a++] = mini->args[mini->xx][j++];
				if (mini->args[mini->xx][j] == ' ' || mini->args[mini->xx][j] < 'A'
					|| (mini->args[mini->xx][j] > 'Z'
					&& mini->args[mini->xx][j] < 'a')
					|| mini->args[mini->xx][j] > 'z')
					break ;
			}
			mini->envvv = ft_get_value_from_env(mini->env, str_to_look);
			if (!mini->envvv)
				continue;
			while (mini->envvv[env] && mini->envvv[env] != ' ')
				new_str[i++] = mini->envvv[env++];
			if (mini->envvv[env] == ' ')
			{
				mini->swit = 1;
				env++;
				break ;
			}
			sw = 0;
		}
		else if (mini->swit == 1)
		{
			while (mini->envvv[env] == ' ')
				env++;
			while (mini->envvv[env] && mini->envvv[env] != ' ')
				new_str[i++] = mini->envvv[env++];
			mini->swit = 0;
			break ;
		}
		else if (mini->args[mini->xx][j] != '\0')
			new_str[i++] = mini->args[mini->xx][j++];
		if (mini->space_flag[mini->xx] == 1 && mini->args[mini->xx][j] == '\0')
			break ;
		if (mini->args[mini->xx][j] == '\0')
		{
			j = 0;
			mini->xx++;
		}
	}
	new_str[i] = '\0';
	return (new_str);
}

int	ft_expand(t_mini *mini)
{
	char	*new_str;
	int		i;

	i = 0;
	mini->swit = 0;
    if (ft_is_builtin(mini, mini->args[0]))
		return (1);
	while (mini->xx < mini->index)
	{
		new_str = ft_get_new_str(mini);
		if (ft_strcmp(new_str, "\0") == 0)
		{
			if (mini->xx != mini->index)
				mini->xx++;
			continue ;
		}
		free(mini->args[i]);
		mini->args[i] = ft_strdup(new_str);
		free(new_str);
		if (mini->swit == 1)
		{
			i++;
			continue ;
		}
		if (mini->args[mini->xx] == NULL)
		{
			i++;
			break ;
		}
		mini->xx++;
		i++;
		mini->swit = 0;
	}
	mini->args[i] = NULL;
	return (0);
}