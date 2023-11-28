
#include "minishell.h"

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
	char	*tmp;
	char	*str;
	size_t	i;

	i = 0;
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
	if (!str)
	{
		str = malloc(sizeof(char) * 1);
		str[0] = '\0';
	}
	else
		str = get_key_value(str);
	free_ptr(tmp);
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
	ret = malloc(sizeof(char) * 1);
	ret[0] = '\0';
	token = erase_quotes(token);
	while (token[i])
	{
		while (token[i] && token[i] != '$')
			i++;
		tmp = malloc(sizeof(char) * (i + 1));
		while (count < i)
			tmp[l++] = token[count++];
		tmp[l] = '\0';
		l = 0;
		ret = ft_strjoin_f(ret, tmp);
		if (!token[i])
			break ;
		str = search_env_var(data, token + i);
		ret = ft_strjoin_f(ret, str);
		while (token[i] && token[i++] != ' ')
			count++;
	}
	free_ptr(token);
	free_ptr(tmp);
	free_ptr(str);
	return (ret);
}

int	check_squotes(char *token)
{
	int	i;
	int	squotes;
	int	dquotes;

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

char *replace_squotes(t_data *data, char *token)
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
