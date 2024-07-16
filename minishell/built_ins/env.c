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

void ft_init_env(t_env_var **tail, t_env_var **head, t_shell *var)
{
	int			num;
	t_env_var	*new_node;
	//char *place_holder;

	num = var->num_env_var;
	*tail = (t_env_var *)safe_malloc(sizeof(t_env_var));
	*head = *tail;
	// num = new_node->num;
	while (num > 0)
	{
		new_node = env_new_node(tail, head);
		num--;
	}
	new_node = new_node;
	//new_node->typ_env = SSH_AUTH_SOCK;
 
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

char	*env_to_str(t_typ_env var)
{
	if (var == 0)
		return ("SSH_AUTH_SOCK");
	else if (var == 1)
		return ("SESSION_MANAGER");
	else if (var == 2)
		return ("GNOME_TERMINAL_SCREEN");
	else if (var == 3)
		return ("SSH_AGENT_PID");
	else if (var == 4)
		return ("LANGUAGE");
	else if (var == 5)
		return ("LANG");
	else
		return(NULL);
}

char	**env_variables(t_env_var *vars)
{
	int		num_vars;
	int		i;
	char **env_array;
	t_env_var	*curr;

	curr = vars;
	i = 0;
	num_vars = 0;
	while(curr)
	{
		num_vars++;
		curr = curr->next;
	}
	env_array = (char **)safe_malloc(sizeof(char *) * num_vars + 1);
	curr = vars;
	i = 0;
	while(curr)
	{
		env_array[i] = ft_strdup(env_to_str(curr->typ_env));
		i++;
		curr = curr->next;
	}
	env_array[i] = NULL;
	return(env_array);
}

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
	t_env_var	**tail;
	t_env_var	**head;
	t_shell		*var; //OVVIAMENTE NON DOVRà RESTARE QUI!
	char		**env_array;
	int	i;

	i = 0;
	tail = NULL;
	head = NULL;
	var = safe_malloc(sizeof(t_shell) * 1);
	var->num_env_var = 49;//OVVIAMENTE NON DOVRà RESTARE QUI!
	ft_init_env(tail, head, var);
	env_array = (char **)safe_malloc(sizeof(char *) * size_list(*tail) + 1);
	env_array = env_variables(*tail);
	while (tail)
	{
		//printf("%s=\n", env_array[i]);
		printf("%s=%s\n", env_array[i], getenv(env_array[i]));
		//printf("%s=%s\n", , getenv());
		*tail = (*tail)->next;
		i++;
	}
}