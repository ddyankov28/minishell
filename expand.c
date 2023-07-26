/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/26 11:38:55 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/26 12:09:06 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

static int	ft_check_new_str(t_mini *mini, char *new_str)
{
	if (ft_strcmp(new_str, "\0") == 0)
	{
		if (mini->xx != mini->index)
			mini->xx++;
		free(new_str);
		return (1);
	}
	return (0);
}

static int	ft_expand_expandation(t_mini *mini, char *new_str, int i)
{
	while (mini->xx < mini->index)
	{
		new_str = ft_get_new_str(mini);
		if (ft_check_new_str(mini, new_str) == 1)
			continue ;
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

int	ft_expand(t_mini *mini)
{
	char	*new_str;
	int		i;

	i = 0;
	mini->swit = 0;
	new_str = NULL;
	if (ft_is_builtin(mini, mini->args[0]))
		return (1);
	ft_expand_expandation(mini, new_str, i);
	return (0);
}
