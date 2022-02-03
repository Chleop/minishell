/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/31 15:23:36 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/02 13:07:13 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_del_stringtab(char ***tab)
{
	int	i;

	i = 0;
	if (!*tab)
		return ;
	while ((*tab)[i])
	{
		if ((*tab)[i])
		{
			free((*tab)[i]);
			(*tab)[i] = NULL;
		}
		i++;
	}
	free(*tab);
	*tab = NULL;
}

void	ft_free_data_cmd(t_data *data)
{
	int	i;

	i = 0;
	while (i < data->nr_cmds)
	{
		if (data->cmd[i].tok)
			ft_del_stringtab(&(data->cmd[i].tok));
		i++;
	}
	free (data->cmd);
	data->cmd = NULL;
}

void	ft_free(t_data *data)
{
	// if (token)
	// 	ft_del_stringtab(&token);
	if (data)
	{
		if (data->cmd)
			ft_free_data_cmd(data);
		data = NULL;
	}
}

int	ft_error(char *str)
{
	printf("%s\n", str);
	return (0);
}

void	final_exit(int i, char *str)
{
	printf("%s\n", str);
	exit (i);
}