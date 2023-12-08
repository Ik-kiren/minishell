/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:47 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/08 14:14:33 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	init_c_t(int *count, int *quotes, int *dquotes)
{
	*count = 0;
	*dquotes = 0;
	*quotes = 0;
}

int	count_tokens(char *line)
{
	int	i;
	int	count;
	int	quotes;
	int	dquotes;

	init_c_t(&count, &quotes, &dquotes);
	i = 0;
	quotes_states2(line, i, &quotes, &dquotes);
	while (line[i])
	{
		if (line[i] != '\0' && line[i] != ' ')
		{
			count++;
			while (line[i] && (line[i] != ' ' || quotes || dquotes))
			{
				if (line[i] == '|' && line[i + 1] != ' ' && line[i + 1] != '\0')
					count++;
				if (line[i + 1] == '|' && line[i] != ' ')
					count++;
				quotes_states2(line, i, &quotes, &dquotes);
				i++;
			}
		}
		if (!line[i])
			break ;
		i++;
	}
	return (count);
}

char	*erase_env_var(char *token)
{
	int		i;
	char	*tmp;

	i = 0;
	if (token[0] == '$')
		return (" ");
	while (token[i] != '$')
		i++;
	tmp = malloc(sizeof(char) * i);
	i = 0;
	while (token[i] != '$')
	{
		tmp[i] = token[i];
		i++;
	}
	tmp[i] = '\0';
	free(token);
	return (tmp);
}

int	parse_env_var(t_data *data, char **tokens)
{
	int	i;
	int	quotes;

	i = 0;
	quotes = 0;
	while (tokens[i])
	{
		if (ft_strchr('$', tokens[i]))
			tokens[i] = replace_squotes(data, tokens[i]);
		else if (check_squotes(tokens[i]))
			tokens[i] = erase_quotes(tokens[i], quotes);
		i++;
	}
	return (1);
}

char	**shell_split_tokens(t_data *data, char *line)
{
	char	**tokens;
	int		nbr_tokens;

	if (line[0] == '\0')
		return (NULL);
	if (!check_op_quotes(line))
		return (print_error("error: unclosed quotes"));
	nbr_tokens = count_tokens(line);
	if (nbr_tokens == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
	if (!tokens)
	{
		free_ptr(line);
		return (NULL);
	}
	malloc_tokens(line, tokens);
	get_tokens(line, tokens);
	if (parse_env_var(data, tokens) == 0)
		return (NULL);
	free_ptr(line);
	return (tokens);
}
