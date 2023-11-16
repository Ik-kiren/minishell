/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokens_split.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/06 10:50:47 by cdupuis           #+#    #+#             */
/*   Updated: 2023/11/16 14:16:12 by cdupuis          ###   ########.fr       */
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
		if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != '\0')
			count++;
		i++;
	}
	return (count);
}

char	**malloc_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	count;

	i = 0;
	j = 0;
	count = 0;
	while (line[i])
	{
		if (line[i] != ' ')
			count++;
		if ((line[i] == ' ' && line[i - 1] != ' ')
			|| (line[i] != ' ' && line[i + 1] == '\0'))
		{
			printf("count_w = %d\n", count);
			tokens[j] = malloc(sizeof(char) * (count + 1));
			if (!tokens[j])
				return (NULL);
			count = 0;
			j++;
		}
		i++;
	}
	return (tokens);
}

char	**get_tokens(char *line, char **tokens)
{
	int	i;
	int	j;
	int	l;

	i = 0;
	j = 0;
	l = 0;
	while (line[i])
	{
		if (line[i] != ' ' && line[i] != '\0')
			tokens[j][l++] = line[i];
		if (line[i] != ' ' && line[i + 1] == '\0')
			tokens[j][l] = '\0';
		if ((line[i] == ' ' || line[i] == '\0') && line[i - 1] != ' ')
		{
			tokens[j][l] = '\0';
			l = 0;
			j++;
		}
		i++;
	}
	tokens[j + 1] = NULL;
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

/*char	*replace_env_var(t_data *data, char *token)
{
	char	*tmp;
	char	*str;
	char	*ret;
	int		i;

	i = 0;
	tmp = get_env_var(data, ft_strchr('$', token) + 1);
	if (!tmp)
		return (erase_env_var(token));
	tmp = get_key_value(tmp);
	while (token[i] != '$')
		i++;
	if (i == 0)
		return (tmp);
	str = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token[i] != '$')
	{
		str[i] = token[i];
		i++;
	}
	str[i] = '\0';
	ret = ft_strjoin(str, tmp);
	free(str);
	free(tmp);
	return (ret);
}*/

char	*replace_env_var(t_data *data, char *token)
{
	char	**tmp;
	char	*str;
	char	*str_tmp;
	int		i;

	tmp = ft_split(token, '$');
	str = "";
	if (token[0] == '$')
		i = 0;
	else
		i = 1;
	if (!tmp[1])
	{
		str = get_env_var(data, tmp[0]);
		if (!str)
			return (erase_env_var(token));
		str = get_key_value(str);
		free(tmp);
		free(token);
		return (str);
	}
	while (tmp[i])
	{
		str_tmp = get_env_var(data, tmp[i]);
		if (!str_tmp)
			str_tmp = "";
		else
			str_tmp = get_key_value(str_tmp);
		str = ft_strjoin(str, str_tmp);
		i++;
	}
	free(tmp);
	free(token);
	if (str_tmp != "")
		free(str_tmp);
	return (str);
}

int check_squotes(char *token)
{
	int	left;
	int	right;
	int	i;

	i = 0;
	left = 0;
	right = 0;
	while (token[i] != '$')
	{
		if (token[i] == '\'')
			left++;
		i++;
	}
	while (token[i] != '\0')
	{
		if (token[i] == '\'')
			right++;
		i++;
	}
	if (left % 2 == 0 && right % 2 == 0)
		return 0;
	return (1);
}

void	parse_env_var(t_data *data, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (tokens[i])
	{
		if (ft_strchr('$', tokens[i]))
			if (check_squotes(tokens[i]) == 0)
				tokens[i] = replace_env_var(data, tokens[i]);
		i++;
	}
}

char	**shell_split_tokens(t_data *data, char *line)
{
	char	**tokens;
	int		nbr_tokens;
	int		i;

	i = 0;
	if (line == NULL)
		exit(EXIT_SUCCESS);
	if (line[0] == '\0')
		return (NULL);
	nbr_tokens = count_tokens(line);
	//printf("count = %d\n", nbr_tokens);
	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
	if (!tokens)
		return (NULL);
	malloc_tokens(line, tokens);
	get_tokens(line, tokens);
	//while (i < nbr_tokens)
		//printf("tokens = %s\n", tokens[i++]);
	parse_env_var(data, tokens);
	return (tokens);
}
