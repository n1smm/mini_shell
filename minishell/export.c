#include "minishell.h"

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
	tmp[0] = ft_substr(new_var, 0, index_nv + 1);
	if (!tmp)
		free(tmp);
	var->num_env_var += 1; //non serve
	while (var->env[i++])
	{
		j = eq_len(var->env[i]);
		if ((ft_strncmp(var->env[i], new_var, j) == 0) && var->env[i])
		{
			tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
			var->env[i] = join_wrapper(tmp[0], tmp[1], 3);
			// flag = 1;
			// printf("NEWW %i) : %s\n", i, var->env[i]);
			//return (var);
		}
		// printf("ENV %i) : %s\n", i, var->env[i]);
	}
	tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
	//tmp[1] = ft_substr(new_var, 1, index_nv);
	i--;
	new =  join_wrapper(tmp[0], tmp[1], 3);
	var->env[i] = (char *)safe_malloc(sizeof(char) * ft_strlen(new) + 1);
	var->env[i] = ft_strdup(new);
	var->env[i + 1] = NULL;
	// printf("LAST %i) : %s\n", i, var->env[i]);
	//return (var);
	// var->env[i] = ft_strjoin(tmp[0], tmp[1]);
	// var->env[i + 1] = NULL; //JOIN WRAPPER
}

int	valid_env_var(char *args)
{
	int j;

	j = 0;
	if (!(ft_strchr(args, '=')))
		return (1);
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
	return (0);
}

void	ft_export(t_shell *var, char **args)
{
	int		i;
	int		index_var;
	//char	**tmp;

	i = 0;
	// tmp = NULL;
	// tmp = tmp;
	var = var;
	args = args;
	index_var = 0;
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
			printf(" ------  VARIABLE : %s   --------\n\n", args[index_var]);
			add_to_env(var, args[index_var]);
		}
		else
			printf("export: `%s': not a valid identifier\n", args[index_var]);
		index_var++;
	}
	return ;
}
