#include "minishell.h"

void	printf_export(t_shell *var)
{
	int	i;

	i = 0;
	while (var->exp[i])
	{
		printf("declare -x: %s\n", var->exp[i]);
		i++;
	}
	printf("\n");
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

static int	check_env_var(char *str, int index)
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

static char	*add_to_env_supp_3(t_shell *var, char *new, char **tmp, int i)
{
	new = ft_strjoin(tmp[0], tmp[1]);
	if (new)
	{
		add_to_garbage(&(var)->garbage, new);
		var->env[i] = ft_strdup(new);
		add_to_garbage(&(var)->garbage, var->env[i]);
		var->env[i + 1] = NULL;
		add_to_garbage(&(var)->garbage, var->env[i + 1]);
	}
	return (new);
}

static char	*add_to_env_supp_2(t_shell *var, char *new, char **tmp, int i)
{
	new = join_wrapper(tmp[0], tmp[1], 0);
	if (new)
	{
		add_to_garbage(&(var)->garbage, new);
		var->env[i] = ft_strdup(new);
		add_to_garbage(&(var)->garbage, var->env[i]);
	}
	return (new);
}

static void	add_env_supp(t_shell *var, char **tmp, char *new_var, int i_nv)
{
	add_to_garbage(&(var)->garbage, tmp);
	tmp[0] = ft_substr(new_var, 0, i_nv + 1);
	add_to_garbage(&(var)->garbage, tmp[0]);
	if (!tmp[0])
	{
		free(tmp);
		return ;
	}
	tmp[1] = ft_substr(new_var, i_nv + 1, ft_strlen(new_var));
	add_to_garbage(&(var)->garbage, tmp[1]);
	if (!tmp[1])
	{
		free(tmp);
		return ;
	}
}

void add_to_env(t_shell *var, char *new_var)
{
	int		i;
	int		index_nv;
	char	**tmp;
	char	*new;
	int		flag;

	flag = 0;
	new = NULL;
	index_nv = eq_len(new_var);
	tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	add_env_supp(var, tmp, new_var, index_nv);
	i = 0;
	while (var->env[i])
	{
		if (ft_strncmp(var->env[i], new_var, index_nv) == 0)
		{
			flag = 1;
			new = add_to_env_supp_2(var, new, tmp, i);
			break ;
		}
		i++;
	}
	if (!flag)
		add_to_env_supp_3(var, new, tmp, i);
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
	s3 = (char *)malloc(sizeof(char) * (ft_strlen(s1) + j + 3));
	if (!s3)
	{
		free(s3);
		return (NULL);
	}
	while (x < ft_strlen(s1))
	{
		s3[y] = s1[y];
		y++;
		x++;
	}
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

static void	add_to_export_supp(t_shell *var, char **tmp, char *new, int *i)
{
	new = ft_strjoin_exp(tmp[0], tmp[1]);
	add_to_garbage(&(var)->garbage, new);
	var->exp[*i] = ft_strdup(new);
	add_to_garbage(&(var)->garbage, var->exp[*i]);
	var->exp[*i + 1] = NULL;
	add_to_garbage(&(var)->garbage, var->exp[*i + 1]);
}

static void	add_exp_supp_2(t_shell *var, char **tmp, char *new_var, int i_nv)
{
	tmp[0] = ft_substr(new_var, 0, i_nv + 1);
	add_to_garbage(&(var)->garbage, tmp[0]);
	tmp[1] = ft_substr(new_var, i_nv + 1, ft_strlen(new_var));
	add_to_garbage(&(var)->garbage, tmp[1]);
}

static void	add_to_export(t_shell *var, char *new_var)
{
	int		i;
	int		index_nv;
	char	**tmp;
	char	*new;
	int		flag;

	flag = 0;
	i = 0;
	new = NULL;
	index_nv = eq_len(new_var);
	tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	add_to_garbage(&(var)->garbage, tmp);
	add_exp_supp_2(var, tmp, new_var, index_nv);
	while (var->exp[i])
	{
		if (ft_strncmp(var->exp[i], new_var, index_nv) == 0)
		{
			flag = 1;
			add_to_export_supp(var, tmp, new, &i);
			break ;
		}
		i++;
	}
	if (!flag)
		add_to_export_supp(var, tmp, new, &i);
}

static void	add_to_export2_supp(t_shell *var, int *i, const char *new_var)
{
	var->exp[*i] = (char *)safe_malloc(sizeof(char) * \
		ft_strlen(new_var) + 1);
	add_to_garbage(&(var->garbage), var->exp[*i]);
	var->exp[*i] = ft_strdup(new_var);
	add_to_garbage(&(var->garbage), var->exp[*i]);
}

static void	add_to_export2(t_shell *var, char *new_var)
{
	int		i;
	int		j;
	int		flag;

	i = 0;
	j = 0;
	if (!var || ! new_var)
		return ;
	flag = 0;
	while (var->exp[i])
	{
		j = eq_len(var->exp[i]);
		if ((ft_strncmp(var->exp[i], new_var, j) == 0) && var->exp[i])
		{
			flag = 1;
			var->exp[i] = ft_strdup(var->exp[i]);
			add_to_garbage(&(var)->garbage, var->exp[i]);
		}
		i++;
	}
	if (flag == 0)
		add_to_export2_supp(var, &i, new_var);
	var->exp[i + 1] = NULL;
	add_to_garbage(&(var->garbage), var->exp[i + 1]);
}

int	valid_env_var(char *args)
{
	int	j;

	j = 0;
	if (args[j] == '\0')
		return (1);
	if (args[j])
	{
		if (args[j] != '_' && !(ft_isalpha(args[j])))
			return (1);
	}
	while (args[j])
	{
		if (args[j] == '=')
		{
			if (check_env_var(args, j) == 1)
				return (1);
			else
				return (0);
		}
		j++;
	}
	if (!(ft_strchr(args, '=')))
		return (2);
	return (0);
}

static void	export_supp(t_shell *var, char *arg, int *flag)
{
	if (valid_env_var(arg) == 0)
	{
		*flag = 1;
		add_to_env(var, arg);
		add_to_export(var, arg);
	}
	else if (valid_env_var(arg) == 1)
	{
		*flag = 1;
		printf("export: `%s': not a valid identifier\n", arg);
	}
	else
	{
		*flag = 1;
		add_to_export2(var, arg);
	}
}

void	ft_export(t_shell *var, char **args)
{
	int		i;
	int		index_var;
	int		flag;

	i = 0;
	var = var;
	args = args;
	index_var = 0;
	flag = 0;
	while (args[i])
	{
		if (ft_strncmp(args[i], "export\0", 7) == 0)
			index_var = i + 1;
		i++;
	}
	while (args[index_var] && args[index_var][0] != '|')
	{
		export_supp(var, args[index_var], &flag);
		index_var++;
	}
	if (flag == 0)
		printf_export(var);
	return ;
}
