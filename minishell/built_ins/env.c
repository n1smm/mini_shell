/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pgiorgi <pgiorgi@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:47 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/06/24 17:48:02 by pgiorgi          ###   ########.fr       */
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
	//place_holder = malloc(1);
	//place_holder[0] = 0;
	new_node->num = 49;
	num = new_node->num;
	while (num-- > -1)
	{
		new_node = env_new_node(tail, head);
	}
	new_node->typ_env = SSH_AUTH_SOCK;
 
}

t_token	*env_new_node(t_env_var **tail, t_env_var **head)
{
	t_env_var	*new_node;

	new_node = safe_malloc(sizeof(t_env_var));
	/* if (!new_node) */
	/* 	return (NULL); */
	new_node->next = NULL;
	new_node->prev = NULL;
	//new_node->num += 1;
	new_node->typ_env += 1;
	*tail = new_node;
	*head = new_node;
	return (new_node);
}

char	**env_variables(t_env_var *env_var, char *var)
{
	int		i;
	char **env_array;

	i = 0;
	env_array = (char *)safe_malloc(sizeof(char *) * env_var->num + 1);
	if (var == NULL)
	{	
		while(env_array[i])
		{
			env_array[i++] = ft_strdup("SSH_AUTH_SOCK");
		}
	}
	else
		return (NULL); //debug
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

void	ft_env(void)
{
	t_env_var	*tail;
	t_env_var	*head;
	char		**env_array;
	int	i;

	i = 0;
	ft_init_env(&tail, &head);
	env_array = (char *)safe_malloc(sizeof(char *) * tail->num + 1);
	env_array = env_variables(tail, NULL);
	while (tail)
	{
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
