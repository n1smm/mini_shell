#include "minishell.h"

int ft_valid_env_var(char *var)
{
    int i;

    i = 0;
    if (ft_isalpha(var[i]) == 0 && var[i] != '_')
        return (1);
    i++;
    while(var[i] && var[i] != '=')
    {
        if (ft_isalnum(var[i]) == 0 && var[i] != '_')
            return (1);
        i++;
    }
    return (0);
}

// int ft_count_env(char **env)
// {
//     int i;

//     i = 0;
//     while(env[i] && env)
//         i++;
// //     return (i);
// // }

// char    **name_value_env(char *var)
// {
//     char    **tmp;
//     char    *eq_index;

//     eq_index = ft_strchr(var, '=');
//     tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
//     tmp[0] = ft_substr(var, 0, eq_index - var);
//     tmp[1] = ft_substr(eq_index, 1, ft_strlen(eq_index));
//     tmp[2] = NULL;
//     return (tmp);
// }

static int check_env_var(char *str, int index)
{
    int i;

    i = 0;
    while(i < index)
    {
        if(!(ft_isalnum(str[i])) && str[i] != '_')
            return (1);
        i++;
    }
    return(0);
}

void add_to_env(t_shell *var, char *new_var)
{
    int i = 0;
    int j = 0;
    int index_nv = 0;
    char **tmp;

    while (new_var[index_nv] != '=')
        index_nv++;
    tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
    tmp[0] = ft_substr(new_var, 0, index_nv + 1);
    if(!tmp)
        free(tmp);
    var->num_env_var += 1;
    while(var->env[i])
    {
        j=0;
        while(var->env[i][j] != '=')
            j++;
        if(ft_strncmp(var->env[i], new_var, j - 1) == 0)
        {
            tmp[1] = ft_substr(new_var, index_nv + 1, ft_strlen(new_var));
            var->env[i] = ft_strjoin(tmp[0], tmp[1]);
            return ;
        }
        i++;
    }
    tmp[1] = ft_substr(new_var, 1, index_nv);
    i += 1;
    var->env[i] = ft_strjoin(tmp[0], tmp[1]);
    var->env[i + 1] = NULL;
    return ;
}

int valid_env_var(char *args)
{
    int j;

    j = 0;
    if(!(ft_strchr(args, '=')))
        return(1);
    if(args[j] == '\0')
        return (1);
    if(args[j])
    {
        if(args[j] != '_' && !(ft_isalpha(args[j])))
            return (1);
    }
    while(args[j])
    {
        if(args[j] == '=')
        {
            if(check_env_var(args, j) == 1)
                return(1);
            else
                return(0);
        }
        j++;
    }
    return (0);

}

void    ft_export(t_shell *var, char **args)
{
    int     i;
    int     index_var;
    char **tmp;

    i = 0;

    i = i;
    tmp = NULL;
    tmp = tmp;
    var = var;
    args = args;
    index_var = 0;
    while(args[i])
    {
        if(ft_strncmp(args[i], "export\0", 7) == 0)
            index_var = i + 1;
        i++;
    }
    while(args[index_var] && args[index_var][0] != '|')
    {
        if(valid_env_var(args[index_var]) == 0)
            add_to_env(var, args[index_var]);
        else
            printf("export: `%s': not a valid identifier\n", args[index_var]);
        index_var++;
    }
    return ;
}