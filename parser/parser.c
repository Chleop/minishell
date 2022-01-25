/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/13 18:55:08 by cproesch          #+#    #+#             */
/*   Updated: 2022/01/24 13:09:37 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	review_operators(char **token)
{
	int	i;

	i = 0;
	while (token[i])
	{
		if ((token[i][0] == '|') || (token[i][0] == '>') || (token[i][0] == '<'))
		{
			if (ft_strncmp(token[i], "|\0", 2) && ft_strncmp(token[i], "<\0", 2)
			&& ft_strncmp(token[i], ">\0", 2) && ft_strncmp(token[i], ">>\0", 3)
			&& ft_strncmp(token[i], "<<\0", 3) && ft_strncmp(token[i], ">|\0", 3))
				return (ft_error("Syntax error"));
			else if (!token[i + 1])
				return (ft_error("Syntax error"));
		}
		i++;
	}
	return (1);
}

int	parse(t_data *data, char **token)
{
	if (!review_operators(token))
		return (0);
	if (!initialize_data(data, token))
		return (0);
	if (!initialize_cmds(data, token))
		return (0);
	if (!grammatize_cmds(data))
		return (0);
	print_cmds_and_tokens(data);
	if (!expand_and_classify_dollars(data))
		return (0);
	// if (!expand_and_classify_others(data))
	// 	return (0);
	print_char_table(data->cmd[0].param);
	return (1);
}