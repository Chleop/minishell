/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_functions_1.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avan-bre <avan-bre@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/01/07 14:28:50 by cproesch          #+#    #+#             */
/*   Updated: 2022/02/01 11:31:09 by avan-bre         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	condition_0(t_lex *lex, char ***token)
{
	create_new_token(token, lex);
}

void	condition_1(t_lex *lex, char ***token)
{
	if (ft_strncmp((*token)[lex->tok_nb - 1], "|\0", 2)
	&& (ft_strchr("|<>", (lex->input)[lex->i])))
		add_to_token(token, lex, (lex->input)[lex->i++]);
	else
	{
		create_new_token(token, lex);
		if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
			condition_2(lex, token);
		else
			add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	condition_2(t_lex *lex, char ***token)
{
	char	c;

	c = lex->input[lex->i];
	add_to_token(token, lex, (lex->input)[lex->i++]);
	if ((is_paired(c, lex->input, lex->i)))
	{
		while (lex->input[lex->i] != c)
			add_to_token(token, lex, (lex->input)[lex->i++]);
		add_to_token(token, lex, (lex->input)[lex->i++]);
	}
}

void	condition_3(t_lex *lex, char ***token)
{
	int	i;

	i = 0;
	add_to_token(token, lex, (lex->input)[lex->i++]);
	while (((lex->input)[lex->i] != ' ') && ((lex->input)[lex->i] != '\n')
	&& ((lex->input)[lex->i] != '\0'))
	{
		if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
			condition_2(lex, token);
		else if ((lex->input)[lex->i] == '$')
			condition_3(lex, token);
		else
			add_to_token(token, lex, (lex->input)[lex->i++]);
		i++;
	}
	return ;
}

void	condition_4(t_lex *lex, char ***token)
{
	if (lex->tok_nb != 0)
		create_new_token(token, lex);
	add_to_token(token, lex, (lex->input)[lex->i++]);
}
