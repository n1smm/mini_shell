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

static int	eq_len(char *str)
{
	int	i;

	i = 0;
	if (!str)
		return (0);
	while (str[i] != '=' && str[i])
		i++;
	return (i);
}

void	add_to_env(t_shell *var, char *new_var)
{
	int		i;
	int		j;
	int		index_nv;
	char	**tmp;
	char	*new;
	// int		flag;

	i = 0;
	j = 0;
	index_nv = eq_len(new_var);
	// flag = 0;
	tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	add_to_garbage(&(var)->garbage, tmp);
	tmp[0] = ft_substr(new_var, 0, index_nv + 1);
	if (!tmp)
		free(tmp);
	add_to_garbage(&(var)->garbage, tmp[0]);
	var->num_env_var += 1; //non serve
	while (var->env[i++])
	{
		j = eq_len(var->env[i]);
		if ((ft_strncmp(var->env[i], new_var, j) == 0) && var->env[i])
		{
			tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
			add_to_garbage(&(var)->garbage, tmp[1]);
			if (tmp[0] && tmp[1])
			{
				var->env[i] = join_wrapper(tmp[0], tmp[1], 0);
				add_to_garbage(&(var)->garbage, var->env[i]);
			}//ft_strjoin(tmp[0], tmp[1]);//join_wrapper(tmp[0], tmp[1], 2);
		}
	}
	tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
	add_to_garbage(&(var)->garbage, tmp[1]);
	i--;
	if (tmp[0] && tmp[1])
	{
		new =  ft_strjoin(tmp[0], tmp[1]);
		add_to_garbage(&(var)->garbage, new);
	} //join_wrapper(tmp[0], tmp[1], 2);
	var->env[i] = (char *)safe_malloc(sizeof(char) * ft_strlen(new) + 1);
	add_to_garbage(&(var)->garbage, var->env[i]);
	var->env[i] = ft_strdup(new);
	add_to_garbage(&(var)->garbage, var->env[i]);
	var->env[i + 1] = NULL;
	add_to_garbage(&(var)->garbage, var->env[i + 1]);
}

char	*ft_strjoin_exp(char const *s1, char const *s2)
{
	char	*s3;
	size_t	j;
	size_t	x;
	size_t	y;

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
	y++;
	while (y < (ft_strlen(s1) + j))
	{
		s3[y] = s2[y - ft_strlen(s1)];
		y++;
	}
	s3[y++] = '"';
	s3[y++] = '\0';
	return ((char *)s3);
}

static void	add_to_export(t_shell *var, char *new_var)
{
	int		i;
	int		j;
	int		index_nv;
	char	**tmp;
	char	*new;
	// int		flag;

	i = 0;
	j = 0;
	index_nv = eq_len(new_var);
	// flag = 0;
	tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	add_to_garbage(&(var)->garbage, tmp);
	tmp[0] = ft_substr(new_var, 0, index_nv + 1);
	add_to_garbage(&(var)->garbage, tmp[0]);
	if (!tmp)
		free(tmp);
	var->num_env_var += 1; //non serve
	while (var->exp[i++])
	{
		j = eq_len(var->env[i]);
		if ((ft_strncmp(var->exp[i], new_var, j) == 0) && var->exp[i])
		{
			tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
			add_to_garbage(&(var)->garbage, tmp[1]);
			if (tmp[0] && tmp[1])
			{
				var->exp[i] = ft_strjoin_exp(tmp[0], tmp[1]);
				add_to_garbage(&(var)->garbage, var->exp[i]);
			} //join_wrapper(tmp[0], tmp[1], 2);
		}
	}
	tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
	add_to_garbage(&(var)->garbage, tmp[1]);
	i--;
	if (tmp[0] && tmp[1])
	{
		new =  ft_strjoin_exp(tmp[0], tmp[1]);
		add_to_garbage(&(var)->garbage, new);
	} //join_wrapper(tmp[0], tmp[1], 2);
	var->exp[i] = (char *)safe_malloc(sizeof(char) * ft_strlen(new) + 1);
	add_to_garbage(&(var)->garbage, var->exp[i]);
	var->exp[i] = ft_strdup(new);
	add_to_garbage(&(var)->garbage, var->exp[i]);
	var->exp[i + 1] = NULL;
	add_to_garbage(&(var)->garbage, var->exp[i + 1]);
}

static void add_to_export2(t_shell *var, char *new_var)
{
	int		i;
	int		j;
	// int		index_nv;
	// char	**tmp;
	// char	*new;
	// int		flag;

	i = 0;
	j = 0;
	// index_nv = eq_len(new_var);
	// flag = 0;
	// tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
	// add_to_garbage((t_token *)var, tmp);
	// tmp[0] = ft_substr(new_var, 0, index_nv + 1);
	// if (!tmp)
	// 	free(tmp);
	// var->num_env_var += 1; //non serve
	if (!var || ! new_var)
		return ;
	while (var->exp[i])
	{
		// j = eq_len(var->env[i]);
		if ((ft_strncmp(var->exp[i], new_var, j) == 1) && var->exp[i])
		{
			// tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
			var->exp[i] = ft_strdup(new_var);
			add_to_garbage(&(var)->garbage, var->exp[i]);//join_wrapper(tmp[0], tmp[1], 3);
		}
		// else if ((ft_strncmp(var->exp[i], new_var, j) == 0) && var->exp[i])
		// {
		// 	var->exp[i] = ft_strdup(new_var);
		// }
		i++;
	}
	// tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
	// i--;
	// new =  join_wrapper(tmp[0], tmp[1], 3);
	var->exp[i] = (char *)safe_malloc(sizeof(char) * ft_strlen(new_var) + 1);
	add_to_garbage(&(var->garbage), var->exp[i]); //non spostare mai sotto la riga successiva! leakka sennò
	var->exp[i] = ft_strdup(new_var);
	add_to_garbage(&(var->garbage), var->exp[i]);
	var->exp[i + 1] = NULL;
	add_to_garbage(&(var->garbage), var->exp[i + 1]);
}

int	valid_env_var(char *args)
{
	int j;

	j = 0;
	// if (!(ft_strchr(args, '=')))
	// {
	// 	// add_to_env(var, args);
	// 	return (0);
	// }
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
	{
		// add_to_env(var, args);
		return (2);
	}
	return (0);
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
		if (valid_env_var(args[index_var]) == 0)
		{
			flag = 1;
			add_to_env(var, args[index_var]);
			add_to_export(var, args[index_var]);
			// add_to_garbage(&(var)->garbage, args[index_var]);
		}
		else if (valid_env_var(args[index_var]) == 1)
		{
			flag = 1;
			printf("export: `%s': not a valid identifier\n", args[index_var]);
		}
		else
		{
			flag = 1;
			add_to_export2(var, args[index_var]);
		}
		index_var++;
	}
	if (flag == 0)
		printf_export(var);
	return ;
}
