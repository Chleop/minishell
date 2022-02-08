/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_quotes_removal.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cproesch <cproesch@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/20 14:51:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/08 12:17:30 by cproesch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

// void	cpy_before_quotes(char **token, char *temp, int firstq_i)
// {
// 	int		start;
// 	int		end;

// 	start = 0;
// 	end = firstq_i;
// 	ft_memcpy(*token + start, temp + start, end - start);
// 	return ;
// }

// void	cpy_ins_quotes(char **token, char *temp, int firstq_i, int secondq_i)
// {
// 	int		start;
// 	int		end;

// 	start = firstq_i;
// 	end = secondq_i;
// 	ft_memcpy(*token + start, temp + start + 1, end - start - 1);
// 	return ;
// }

// void	cpy_after_quotes(char **token, char *temp, int secondq_i)
// {
// 	int		start;
// 	int		end;

// 	start = secondq_i;
// 	end = ft_strlen(temp);
// 	ft_memcpy(*token + start - 1, temp + start + 1, end - start - 1);
// 	return ;
// }

// int	remove_quotes(char **token, int firstq_i, int secondq_i)
// {
// 	char	*temp;

// 	temp = *token;
// 	*token = ft_calloc(ft_strlen(temp) - 1, sizeof(char));
// 	if (!*token)
// 		return (0);
// 	cpy_before_quotes(token, temp, firstq_i);
// 	cpy_ins_quotes(token, temp, firstq_i, secondq_i);
// 	if ((temp[secondq_i]) && (temp[secondq_i + 1]))
// 		cpy_after_quotes(token, temp, secondq_i);
// 	free (temp);
// 	temp = NULL;
// 	return (1);
// }

// int	if_remove_quotes(char ***tab, int nr_elements, t_data *data)
// {
// 	int	firstq_i;
// 	int	secondq_i;
// 	int	quote;
// 	int	j;

// 	j = 0;
// 	while (j < nr_elements)
// 	{
// 		quote = is_quoted((*tab)[j]);
// 		if (quote)
// 		{
// 			firstq_i = ft_strchr((*tab)[j], quote) - (*tab)[j];
// 			secondq_i = ft_strchr((*tab)[j] + firstq_i + 1, quote) - (*tab)[j];
// 			if (!remove_quotes(*tab, firstq_i, secondq_i))
// 			{
// 				ft_error2("Error: malloc failed", data, 1);
// 				return (0);
// 			}
// 		}
// 		j++;
// 	}
// 	return (1);
// }

int	if_remove_quotes(char ***tab, int nr_elements, t_data *data)
{
	char	quote;
	int		j;
	char	*temp;
	char	**subtoken;

	j = 0;
	while (j < nr_elements)
	{
		quote = is_quoted((*tab)[j]);
		if (quote)
		{
			printf("Dans remove quotes, (*tab)[j]   1   = %s\n", (*tab)[j]);
			subtoken = ft_split((*tab)[j], quote);
			if (!subtoken)
				return (0);
			temp = (*tab)[j];
			(*tab)[j] = join_and_expand_subparam(data, subtoken, NULL);
			printf("Dans remove quotes, (*tab)[j]   2   = %s\n", (*tab)[j]);
			free(temp);
			ft_del_stringtab(&subtoken);
			return (1);
		}
		j++;
	}
	return (1);
}