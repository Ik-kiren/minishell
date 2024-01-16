#include "minishell.h"

static void	check_args_n(char **tokens, int *_n)
{
	int			i;
    int         j;

    j = 1;
		while (tokens[j])
		{ 
            i = 0;
			if (tokens[j][0] == '-' && tokens[j][1] == 'n')
			{
				i = 2;
				while (tokens[j][i] == 'n')
					i += 1;
				if (tokens[j][i])
					*_n = 0;
				else
					*_n = 1;
			}
			else
				*_n = 0;
            j++;
		}
}

static int	_echo_finalise(t_cmd *cmd, int n, char *str)
{
	int		ret;

	ret = 0;
	if (n)
		ft_printf("%s", str);
	else
		ft_printf("%s\n", str);
	cmd->status_code = ret;
	a->lsc = ret;
	return (ret);
}

int	_echo(char **tokens)
{
	int		n;
    int     _n;
	char	*str;

    _n = 0;
	check_args_n(tokens, &_n);
	n = 0;
	str = "";
	while (tokens && _n)
	{
		n = 1;
		tokens++;
	}
	while (tokens)
	{
		if (ft_strlen(str) > 0)
			str = ft_strjoin(ft_strjoin(str, " "), \
				cmd->args->arg);
		else
			str = ft_strjoin(str, cmd->args->arg);
		cmd->args = cmd->args->next;
	}
	return (_echo_finalise(cmd, n, str));
}
