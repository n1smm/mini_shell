#include "minishell.h"
#include <stdio.h>

static void	strj_exp_iter(size_t *x, const char *s1, size_t *y, char *s3)
{
	while (*x < ft_strlen(s1))
	{
		s3[*y] = s1[*y];
		(*y)++;
		(*x)++;
	}
}

char	*ft_strjoin_exp(char const *s1, char const *s2)
{
	char	*s3;
	size_t	j;
	size_t	x;
	size_t	y;
	size_t	n;

	j = ft_strlen(s2);
	x = 0;
	y = 0;
	s3 = (char *)safe_malloc(sizeof(char) * (ft_strlen(s1) + j + 3));
	strj_exp_iter(&x, s1, &y, s3);
	s3[y] = '"';
	n = y;
	y++;
	while (n < (ft_strlen(s1) + j))
	{
		s3[y] = s2[n - ft_strlen(s1)];
		y++;
		n++;
	}
	s3[y++] = '"';
	s3[y++] = '\0';
	return ((char *)s3);
}

int	ft_valid_env_var(char *var)
{
	int	i;

	i = 0;
	if (ft_isalpha(var[i]) == 0 && var[i] != '_')
		return (1);
	i++;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalnum(var[i]) == 0 && var[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	check_env_var(char *str, int index)
{
	int	i;

	i = 0;
	while (i < index)
	{
		if (!(ft_isalnum(str[i])) && str[i] != '_')
			return (1);
		i++;
	}
	return (0);
}

int	eq_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}
