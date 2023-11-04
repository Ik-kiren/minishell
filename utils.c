#include "minishell.h"

size_t ft_ptrlen(char **str)
{
    size_t i;

    i = 0;
    while (str[i] != NULL)
        i++;
    return i;
}

size_t ft_strlen(const char *str)
{
    size_t i;

    i = 0;
    while (str[i])
        i++;
    return i;
}

char *ft_strdup(char *str)
{
    char *tmp;
    int len;
    int i;

    i = 0;
    len = ft_strlen(str);
    tmp = malloc(sizeof(char) * (len + 1));
    if (!tmp)
        return NULL;
    while (str[i])
    {
        tmp[i] = str[i];
        i++;
    }
    tmp[i] = '\0';
    return tmp;
}

int free_ptr(char **ptr)
{
    int i;

    i = 0;
    while (ptr[i])
    {
        free(ptr[i++]);
    }
    free(ptr);
    return 1;
}

char	*ft_strjoin(char const *s1, char const *s2)
{
	char	*s;
	size_t	len;
	int		i;

	len = ft_strlen(s1) + ft_strlen(s2);
	s = malloc(sizeof(char) * (len + 1));
	if (!s)
		return (NULL);
	len = 0;
	while (s1[len])
	{
		s[len] = s1[len];
		len++;
	}
	i = 0;
	while (s2[i])
	{
		s[len + i] = s2[i];
		i++;
	}
    s[len + i] = '\0';
	return (s);
}

void get_allenv(char **envp)
{
    int i;

    i = 0;
    while (envp[i])
    {
        printf("%d   %s\n", i, envp[i]);
        i++;
    }
}

void free_str(char *str)
{
    if (str != NULL)
    {
        free(str);
        str = NULL;
    }
}