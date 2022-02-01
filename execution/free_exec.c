/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/01 15:54:42 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/01 18:44:44 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_io(t_cmd *cmd)
{
	int	i;

	i = -1;
	while (++i < cmd->nr_out)
	{
		close(cmd->fd_o[i]);
		cmd->fd_o[i] = 0;
	}
	free(cmd->fd_o);
}

void	free_dir_tab(char **dir_tab)
{
	int	i;

	i = -1;
	while (dir_tab[++i])
	{
		if (dir_tab[i])
		{
			free(dir_tab[i]);
			dir_tab[i] = NULL;
		}
	}
	if (dir_tab)
	{
		free(dir_tab);
		dir_tab = NULL;
	}
}
