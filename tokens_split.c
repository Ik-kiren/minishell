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
					return 0;
				i++;
			}
			i++;
			if(line[i] == '\0')
				break;
		}
		if (line[i] == ' ' && line[i + 1] != ' ' && line[i + 1] != '\0' && line[i + 1] != '\"')
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
				break;
		}
		if (line[i] != ' ')
			count++;
		if ((line[i] == ' ' && line[i - 1] != ' ')
			|| (line[i] != ' ' && line[i + 1] == '\0'))
		{
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

char	*erase_quotes(char *token)
{
	char	*tmp;
	int		i;
	int		j;
	int		count;

	i = 0;
	j = 0;
	count = 0;
	while (token[i])
	{
		if (token[i] != '\"' && token[i] != '\'')
			count++;
		i++;
	}
	tmp = malloc(sizeof(char) * (count + 1));
	i = 0;
	while (token[i])
	{
		if (token[i] != '\"' && token[i] != '\'')
		{
			tmp[j] = token[i];
			j++;
		}
		i++;
	}
	tmp[j] = '\0';
	free(token);
	return (tmp);
}

char	*search_env_var(t_data	*data, char	*token)
{
	size_t	len;
	char	*tmp;
	char	*str;
	size_t	i;

	i = 0;
	len = ft_strlen(token);
	while (token[i] && token[i] != '\"' && token[i] != ' ')
		i++;
	tmp = malloc(sizeof(char) * (i + 1));
	i = 0;
	while (token[i] && token[i] != '\"' && token[i] != ' ')
	{
		tmp[i] = token[i];
		i++;
	}
	tmp[i] = '\0';
	str = get_env_var(data, tmp + 1);
	str = get_key_value(str);
	return (str);
}

char	*replace_env_var(t_data *data, char *token)
{
	char	*tmp;
	char	*ret;
	char	*str;
	int		i;
	int		count;
	int		l;

	i = 0;
	count = 0;
	l = 0;
	ret = "";
	token = erase_quotes(token);
	while (token[i])
	{
		while (token[i] && token[i] != '$')
			i++;
		tmp = malloc(sizeof(char) * (i + 1));
		while (count < i)
		{
			printf("l, count = %d, %d\n", l, count);
			tmp[l++] = token[count++];
		}
		tmp[l] = '\0';
		l = 0;
		ret = ft_strjoin(ret, tmp);
		if (!token[i])
			break;
		str = search_env_var(data, token + i);
		ret = ft_strjoin(ret, str);
		while (token[i + 1] && token[i++] != ' ')
			count++;
		i++;
	}
	free_ptr(tmp);
	free_ptr(str);
	return (ret);
}

/*char	*replace_env_var(t_data *data, char *token)
{
	char	**tmp;
	char	*str;
	char	*str_tmp;
	int		i;

	token = erase_quotes(token);
	tmp = ft_split(token, '$');
	str = "";
	i = 0;
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
		printf("TEST = %s\n", tmp[i]);
		str_tmp = get_env_var(data, tmp[i]);
		if (!str_tmp)
			str = ft_strjoin(str, tmp[i]);
		else
		{
			str_tmp = get_key_value(str_tmp);
			str = ft_strjoin(str, str_tmp);
		}
		i++;
	}
	free(tmp);
	free(token);
	if (str_tmp[0] != '\0')
		free_ptr(str_tmp);
	return (str);
}*/

int	check_squotes(char *token)
{
	int	i;
	int	squotes;
	int dquotes;
	
	squotes = 0;
	dquotes = 1;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && squotes == 0)
			squotes = 1;
		else if (token[i] == '\'' && squotes == 1)
			squotes = 0;
		if (token[i] == '\"' && dquotes == 0)
			dquotes = 1;
		else if (token[i] == '\"' && dquotes == 1)
			dquotes = 0;
		i++;
	}
	if (squotes == 1 || dquotes == 0)
		return (0);
	return (1);
}

char *replace_squotes(t_data *data,char *token)
{
	int	i;
	int	squotes;
	int dquotes;
	int none;

	squotes = 0;
	dquotes = 1;
	none = 0;
	i = 0;
	while (token[i])
	{
		if (token[i] == '\'' && squotes == 0)
		{
			none = 1;
			squotes = 1;
		}
		else if (token[i] == '\'' && squotes == 1)
			squotes = 0;
		if (token[i] == '\"' && dquotes == 0)
			dquotes = 1;
		else if (token[i] == '\"' && dquotes == 1)
		{
			none = 1;
			dquotes = 0;
		}
		if ((token[i] == '$' && squotes == 0) && dquotes == 0)
			return (replace_env_var(data, token));
		i++;
	}
	if (none == 0)
		return (replace_env_var(data, token));
	return (token);
}

int	parse_env_var(t_data *data, char **tokens)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
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
	int		i;

	i = 0;
	if (line[0] == '\0')
		return (NULL);
	nbr_tokens = count_tokens(line);
	if (nbr_tokens == 0)
		return (NULL);
	tokens = malloc(sizeof(char *) * (nbr_tokens + 1));
	if (!tokens)
		return (NULL);
	malloc_tokens(line, tokens);
	get_tokens(line, tokens);
	if (parse_env_var(data, tokens) == 0)
		return (NULL);
	free_ptr(line);
	return (tokens);
}
