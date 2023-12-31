/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cdupuis <cdupuis@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/10 13:34:40 by cdupuis           #+#    #+#             */
/*   Updated: 2023/12/11 10:07:38 by cdupuis          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*find_path(t_cmd *cmd, char **paths)
{
	char	*tmp;
	char	*path;
	int		i;

	i = 0;
	while (paths[i])
	{
		tmp = ft_strjoin(paths[i], "/");
		if (!tmp)
			return (NULL);
		path = ft_strjoin(tmp, cmd->cmd);
		if (!path)
			return (NULL);
		if (access(path, F_OK | X_OK) == 0)
		{
			free_ptr(tmp);
			return (path);
		}
		free_ptr(tmp);
		free_ptr(path);
		i++;
	}
	return (cmd->cmd);
}

char	*get_path(t_data *data, t_cmd *cmd)
{
	char	**paths;
	char	*path;
	int		idx;

	idx = get_env_idx(data, "PATH");
	if (idx == -1)
		return ("");
	paths = ft_split(data->env[idx], ':');
	if (!paths)
		return (NULL);
	path = find_path(cmd, paths);
	if (!path)
		return (NULL);
	free_str(paths);
	return (path);
}
