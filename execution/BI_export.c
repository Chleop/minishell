/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/14 16:43:49 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/22 12:04:37 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	reset_printed(t_envp *envp)
{
	t_envp	*temp;

	temp = envp;
	while (temp)
	{
		temp->printed = 0;
		temp = temp->next;
	}
}

int	smaller_ascii(char *str1, char *str2)
{
	size_t	i;
	size_t	size;
	size_t	size1;
	size_t	size2;

	size1 = ft_strlen(str1);
	size2 = ft_strlen(str2);
	size = size1;
	if (size2 < size)
		size = size2;
	i = -1;
	while (++i < size)
	{
		if (str1[i] < str2[i])
			return (1);
		if (str1[i] > str2[i])
			return (0);
	}
	if (size < size2)
		return (1);
	else
		return (0);
}

t_envp	*get_smallest_unprinted(t_envp *envp, int size)
{
	t_envp	*temp;
	t_envp	*min;
	int		i;

	temp = envp;
	while (temp->printed)
		temp = temp->next;
	min = temp;
	temp = envp;
	i = -1;
	while (++i < size)
	{
		if (temp->printed == 0 && smaller_ascii(temp->name, min->name))
			min = temp;
		temp = temp->next;
	}
	return (min);
}

void	ft_export_fork(t_cmd *cmd)
{
	t_envp	*temp;
	t_envp	*min;
	int		size;
	int		i;

	size = size_list(cmd->data->envp);
	temp = cmd->data->envp;
	i = -1;
	while (++i < size)
	{
		min = get_smallest_unprinted(temp, size);
		if (min->var)
			ft_printf("%s %s=\"%s\"\n", 1, "declare -x", min->name, min->var);
		else
			ft_printf("%s %s\n", 1, "declare -x", min->name);
		min->printed++;
	}
	reset_printed(temp);
	g_lobal.exit_code = 0;
}
