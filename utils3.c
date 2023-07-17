/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vstockma <vstockma@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/07/17 15:32:34 by vstockma          #+#    #+#             */
/*   Updated: 2023/07/17 15:32:56 by vstockma         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mini.h"

char* ft_get_current_path(t_mini *mini)
{
    char* path = malloc(sizeof(char) * 1024);
    if (path == NULL)
        ft_free_malloc(mini);   
    if (getcwd(path, 1024) == NULL)
    {
        perror("getcwd() error");
        free(path);
        return NULL;
    }
    return (path);
}
