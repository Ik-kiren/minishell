/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:47 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/28 14:20:57 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	count_tokens(char *line)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	if (line[0] != ' ')
		count++;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			count++;
			i++;
			while (line[i] != '\"')
			{
				if (line[i] == '\0')
					return (0);
				i++;
			}
			i++;
			if (line[i] == '\0')
				break ;
		}
		if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '\"')
			count++;
		i++;
	}
	return (count);
}

void	malloc_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] == '\"')
		{
			i++;
			while (line[i] != '\"')
			{
				count++;
				i++;
			}
			count += 2;
			i++;
			tokens[j++] = malloc(sizeof(char) * (count + 1));
			count = 0;
			if (line[i] == '\0')
				break ;
		}
		if (line[i] != ' ')
			count++;
		if ((line[i] == ' ' && line[i - 1] != ' ')
			|| (line[i] != ' ' && line[i + 1] == '\0'))
		{
			tokens[j] = malloc(sizeof(char) * (count + 1));
			if (!tokens[j])
				tokens[j] = NULL;
			count = 0;
			j++;
		}
		i++;
	}
}

char	**get_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	l;
	int	status;

	i = 0;
	j = 0;
	l = 0;
	status = 0;
	while (line[i])
	{
		l = 0;
		if (line[i] == '\"')
		{
			status = 1;
			while (status == 1)
			{
				tokens[j][l++] = line[i++];
				if (line[i] == '\"')
					status = 0;
			}
			tokens[j][l++] = line[i];
			tokens[j][l] = '\0';
			j++;
		}
		else if (line[i] != '\0' && line[i] != ' ')
		{
			while (line[i] != '\0' && line[i] != ' ')
				tokens[j][l++] = line[i++];
			tokens[j][l] = '\0';
			j++;
		}
		if (line[i])
			i++;
	}
	tokens[j] = NULL;
	return (tokens);
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

	i = 0;
	while (tokens[i])
	{
		if (!ft_strcmp("$?", tokens[i]))
			tokens[i] = data->ret;
		if (ft_strchr('$', tokens[i]) && check_squotes(tokens[i]))
			tokens[i] = replace_squotes(data, tokens[i]);
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
