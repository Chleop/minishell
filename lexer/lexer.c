#include "minishell.h"

void	init_lexer(t_lex *lex, char *input)
{
	lex->input = input;
	lex->i = 0;
	lex->token_nb = 0;
	lex->tok_char_nb = 0;
}

int	condition_tree(t_lex *lex, char ***token)
{
	if (!(*token))
		return (0);
	if ((ft_strchr("|<>", (lex->input)[lex->i - 1])) && ((lex->i - 1) >= 0))
		return (1);
	if (((lex->input)[lex->i] == '\'') || ((lex->input)[lex->i] == '\"'))
		return (2);
	if ((lex->input)[lex->i] == '$')
		return (3);
	if (ft_strchr("|<>", (lex->input)[lex->i]))
		return (4);
	if ((lex->input)[lex->i] == ' ')
		return (5);
	if ((!(ft_strchr("|<> ", (lex->input)[lex->i - 1]))) && (lex->i - 1 >= 0))
		return (6);
	return (7);
}

char	**split_into_token(char *input)
{
	t_lex		*lex;
	char		**token;
	int			met_condition;
	static void	(*function_table[9])(t_lex *lex, char ***token) = {
		condition_0,
		condition_1,
		condition_2,
		condition_3,
		condition_4,
		condition_5,
		condition_6,
		condition_7,
		NULL,
	};

	lex = ft_calloc(1, sizeof(t_lex));
	init_lexer(lex, input);
	token = NULL;
	int j = 0;
	while (((lex->input)[lex->i] != '\n') && (j < 10))
	{
		met_condition = condition_tree(lex, &token);
		function_table[met_condition](lex, &token);
		j++;
	}
	return (token);
}