/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:47 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/28 14:08:30 by pgiorgi          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_init_env(t_env_var **tail, t_env_var **head)
{
	int			num;
	t_env_var	*new_node;
	//char *place_holder;

	*tail = (t_env_var *)safe_malloc(sizeof(t_env_var));
	*head = *tail;
	num = 49;
	// num = new_node->num;
	while (num-- > -1)
	{
		new_node = env_new_node(tail, head);
	}
	new_node->typ_env = SSH_AUTH_SOCK;
 
}

t_env_var	*env_new_node(t_env_var **tail, t_env_var **head)
{
	t_env_var	*new_node;

	new_node = safe_malloc(sizeof(t_env_var));
	/* if (!new_node) */
	/* 	return (NULL); */
	new_node->next = NULL;
	new_node->prev = NULL;
	new_node->num += 1;
	new_node->typ_env += 1;
	*tail = new_node;
	*head = new_node;
	return (new_node);
}

char	**env_variables(void)
{
	int		i;
	int		j;
	char **env_array;

	i = 49;
	j = 0;
	//(void)env_var;
	env_array = (char **)safe_malloc(sizeof(char *) * i + 1);
	while(i > -1)
	{
		env_array[j] = ft_strdup("SSH_AUTH_SOCK");
		env_array[j + 1] = ft_strdup("SESSION_MANAGER");
		i--;
	}
	return(env_array);
}

// char	*each_env(char **env_array, int index)
// {
// 	char *curr_env;

// 	if (index < 0 || !env_var)
// 		return (NULL);
// 	curr_env = ft_strdup(env_var[index]);
// 	return(env_var);
// }

int	size_list(t_env_var *tail)
{
	int i;

	i  = 0;
	while(tail)
	{
		tail = tail->next;
		i++;
	}
	return (i);
}

void	ft_env(void)
{
	t_env_var	*tail;
	t_env_var	*head;
	char		**env_array;
	int	i;

	i = 0;
	ft_init_env(&tail, &head);
	env_array = (char **)safe_malloc(sizeof(char *) * size_list(tail) + 1);
	env_array = env_variables();
	while (tail)
	{
		//printf("%s=\n", env_array[i]);
		printf("%s=%s\n", env_array[i], getenv(env_array[i]));
		//printf("%s=%s\n", , getenv());
		tail = tail->next;
		i++;
	}
	//printf("%s\n", getenv("PATH"));
	// if (getenv("SSH_AUTH_SOCK") != NULL)
	// {
	// 	printf("SSH_AUTH_SOCK=%s\n", getenv("SSH_AUTH_SOCK"));
		

	// }
	// else
	// {
	// 	printf("env error\n"); 
	// }
}
