/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   BI_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/07 15:06:37 by avan-bre          #+#    #+#             */
/*   Updated: 2022/02/17 14:45:03 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*get_var(t_envp *envp, char *name)
{
	t_envp	*temp;

	temp = envp;
	while (temp)
	{
		if (!ft_strncmp(name, temp->name, ft_strlen(temp->name)))
			return (ft_strdup(temp->var));
		temp = temp->next;
	}
	return (NULL);
}

void	finish_cd(t_data *data, t_cd *cd)
{
	char	*temp;
	char	*pwd;

	if (cd->oldpwd)
	{
		temp = ft_strjoin("OLDPWD=", cd->oldpwd);
		add_to_envp(data->envp, temp);
		free_string(&temp);
	}
	pwd = get_var(data->envp, "PWD");
	if (pwd)
	{
		temp = ft_strjoin("PWD=", cd->path);
		add_to_envp(data->envp, temp);
		free_string(&temp);
		free_string(&pwd);
	}
}

void	chdir_path(t_data *data, t_cd *cd)
{
	if (cd->path)
	{
		if (chdir(cd->path) == -1)
			ft_error2(strerror(errno), cd->path, data, 1);
		else
			finish_cd(data, cd);
	}
	free_cd(&cd);
}

void	set_path_envp(t_data *data, t_cd *cd, char *name)
{
	t_envp	*temp;

	temp = data->envp;
	while (temp)
	{
		if (ft_strncmp(name, temp->name, ft_strlen(temp->name)) == 0
			&& temp->var)
		{
			cd->path = ft_strdup(temp->var);
			return ;
		}
		temp = temp->next;
	}
	ft_error2("cd: variable not set:", name, data, 1);
}

void	ft_cd(t_cmd *cmd)
{
	t_cd	*cd;

	cd = NULL;
	if (!init_cd(cmd, &cd))
		return ;
	if (!cmd->param[1])
		set_path_envp(cmd->data, cd, "HOME");
	else if (cmd->param[1][0] == '-' && cmd->param[1][1] == '\0')
		set_path_envp(cmd->data, cd, "OLDPWD");
	else if (cmd->param[1][0] == '/')
		set_curpath(cmd->data, cd, cmd->param[1]);
	else
		set_path_dots(cmd, cd);
	chdir_path(cmd->data, cd);
}
