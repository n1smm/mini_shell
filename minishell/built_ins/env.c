/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/06/12 17:07:47 by pgiorgi           #+#    #+#             */
/*   Updated: 2024/07/18 17:39:11 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_init_env(t_env_var **tail, t_env_var **head, char **env)
{
    int num;

	while (env[num])
		num++;
    //num = var->num_env_var;
    *head = NULL;
    *tail = NULL;
    
    while (num > 0)
    {
        env_new_node(tail, head, env);
        num--;
    }
}

t_env_var *env_new_node(t_env_var **tail, t_env_var **head, char **env)
{
    t_env_var *new_node;
    static int count = 0;

    new_node = safe_malloc(sizeof(t_env_var));
    new_node->next = NULL;
    new_node->prev = *tail;
    new_node->num = count;
	env = env;
    //new_node->env[count] = ft_strdup((const char*)env[count]);

    if (*tail)
        (*tail)->next = new_node;
    else
        *head = new_node;

    *tail = new_node;
    count++;
    return new_node;
}

char	**env_variables(t_env_var *var)
{
	int		num_vars;
	int		i;
	char **env_array;
	t_env_var	*curr;

	curr = var;
	i = 0;
	num_vars = 0;
	while(curr)
	{
		num_vars++;
		curr = curr->next;
	}
	env_array = (char **)safe_malloc(sizeof(char *) * num_vars + 1);
	curr = var;
	i = 0;
	while(curr)
	{
		//env_array[i] = ft_strdup(env_to_str(var->env[i]));
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

void ft_env(t_env_var *var, char **env)
{
	int			i;
    t_env_var   *tail;
    t_env_var   *head;
    //t_shell     *var;
    t_env_var   *curr;
   // int         i;
    char        *equal_sign;
	char *env_name = "";

	i = 0;
    tail = NULL;
    head = NULL;
    
    ft_init_env(&tail, &head, env);
    
    curr = head;
    while (var->env[i])
    {
        //char *env_name = env_to_str(var->env[i]);
        if (env_name)
        {
            i = 0;
            while (env[i])
            {
                equal_sign = strchr(env[i], '=');
                if (equal_sign)
                {
                    size_t name_length = equal_sign - env[i];
                    if (strncmp(env[i], env_name, name_length) == 0 && env_name[name_length] == '\0')
                    {
                        printf("%s\n", env[i]);
                        break;
                    }
                }
                i++;
            }
        }
        curr = curr->next;
    }
    free(var);
}

// char	*env_to_str(t_typ_env var)
// {
// 	if (var == 0)
// 		return ("SSH_AUTH_SOCK");
// 	else if (var == 1)
// 		return ("SESSION_MANAGER");
// 	else if (var == 2)
// 		return ("GNOME_TERMINAL_SCREEN");
// 	else if (var == 3)
// 		return ("SSH_AGENT_PID");
// 	else if (var == 4)
// 		return ("LANGUAGE");
// 	else if (var == 5)
// 		return ("LANG");
// 	else if (var == 6)
// 		return ("XDG_CURRENT_DESKTOP");
// 	else if (var == 7)
// 		return ("IM_CONFIG_PHASE");
// 	else if (var == 8)
// 		return ("XDG_GREETER_DATA_DIR");
// 	else if (var == 9)
// 		return ("COLORTERM");
// 	else if (var == 10)
// 		return ("LIBVIRT_DEFAULT_URI");
// 	else if (var == 11)
// 		return ("GPG_AGENT_INFO");
// 	else if (var == 12)
// 		return ("DESKTOP_SESSION");
// 	else if (var == 13)
// 		return ("USER");
// 	else if (var == 14)
// 		return ("XDG_MENU_PREFIX");
// 	else if (var == 16)
// 		return ("XDG_SESSION_PATH");
// 	else if (var == 17)
// 		return ("QT_IM_MODULE");
// 	else if (var == 18)
// 		return ("NO_PROXY");
// 	else if (var == 20)
// 		return ("HOME");
// 	else if (var == 21)
// 		return ("DBUS_SESSION_BUS_ADDRESS");
// 	else if (var == 22)
// 		return ("DOCKER_HOST");
// 	else if (var == 23)
// 		return ("GTK_MODULES");
// 	else if (var == 24)
// 		return ("XDG_CONFIG_DIRS");
// 	else if (var == 25)
// 		return ("VTE_VERSION");
// 	else if (var == 26)
// 		return ("JOURNAL_STREAM");
// 	else if (var == 27)
// 		return ("XDG_SESSION_DESKTOP");
// 	else if (var == 28)
// 		return ("KRB5CCNAME");
// 	else if (var == 29)
// 		return ("GNOME_DESKTOP_SESSION_ID");
// 	else if (var == 30)
// 		return ("MANAGERPID");
// 	else if (var == 31)
// 		return ("QT_ACCESSIBILITY");
// 	else if (var == 32)
// 		return ("XDG_SEAT_PATH");
// 	else if (var == 33)
// 		return ("LOGNAME");
// 	else if (var == 34)
// 		return ("GNOME_TERMINAL_SERVICE");
// 	else if (var == 35)
// 		return ("PATH");
// 	else if (var == 36)
// 		return ("XMODIFIERS");
// 	else if (var == 37)
// 		return ("SHELL");
// 	else if (var == 38)
// 		return ("XDG_SESSION_TYPE");
// 	else if (var == 39)
// 		return ("no_proxy");
// 	else if (var == 40)
// 		return ("DBUS_STARTER_BUS_TYPE");
// 	else if (var == 41)
// 		return ("INVOCATION_ID");
// 	else if (var == 42)
// 		return ("SHLVL");
// 	else if (var == 43)
// 		return ("XAUTHORITY");
// 	else if (var == 44)
// 		return ("GDM_LANG");
// 	else if (var == 45)
// 		return ("DBUS_STARTER_ADDRESS");
// 	else if (var == 46)
// 		return ("DISPLAY");
// 	else if (var == 47)
// 		return ("TERM");
// 	else if (var == 48)
// 		return ("GDMSESSION");
// 	else if (var == 49)
// 		return ("XDG_SESSION_CLASS");
// 	else if (var == 49)
// 		return ("PWD");
// 	else if (var == 49)
// 		return ("OLDPWD");
// 	else
// 		return(NULL);
// }