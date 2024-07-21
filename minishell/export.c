#include "minishell.h"

/* una variabile d'ambiente può essere solo alphanumerica o contenere _*/
/* può iniziare solo con una lettera! mai con un numero*/

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

char    **update_env(t_shell *var, int size)
{
    int     i;
    char    **env;

    i = 0;
    env = ft_calloc(size + 1, sizeof(env));
    if (!env)
        return (0);
    while (i < size && var->env[i])
    {
        env[i] = ft_strdup(var->env[i]);
        i++;
    }
    return(env);
}

int ft_count_env(char **env)
{
    int i;

    i = 0;
    while(env[i] && env)
        i++;
    return (i);
}

int ft_var_index(char **env, char *name)
{
    int i;
    char *tmp;

    i = 0;
    tmp = ft_strjoin(name, "=");
    while (env[i])
    {
        if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
        {
            //free(tmp);or garbage collector?
            return (1);
        }
        i++;
    }
    //free(tmp); or garbage collector?
    return (-1);
}

/* se la variabile (name) già esiste, vado a sovrascrivere
il suo value*/
int    set_env_var(t_shell *var, char *name, char *value)
{
    int index;
    char *tmp;

    index = ft_var_index(var->env, name);
    //var->num_env_var = ft_count_env(var->env);
    if (!value)
        value = "";
    tmp = ft_strjoin("=", value);
    if (!tmp)
        return (1);
    var->env = update_env(var, index + 1);
    if (!var->env)
        return (1);
    var->env[index] = ft_strjoin(name, tmp);
    //free(tmp);
    return (0);
}

char    **name_value_env(char *var)
{
    char    **tmp;
    char    *eq_index;

    eq_index = ft_strchr(var, '=');
    tmp = (char **)safe_malloc(sizeof(char *) * 2 + 1);
    tmp[0] = ft_substr(var, 0, eq_index - var);
    tmp[1] = ft_substr(eq_index, 1, ft_strlen(eq_index));
    tmp[2] = NULL;
    return (tmp);
}

static int check_env_var(char *str, int index)
{
    int i;

    i = 0;
    printf("STR %s\n", str);
    while(i < index)
    {
        if(!(str[i] >= 'a' && str[i] <= 'z') && !(str[i] >= 'A' && str[i] <= 'Z') \
            && !(str[i] >= '0' && str[i] <= '9') && str[i] != '_')
            return (1);
        i++;
    }
    return(0);
}

int valid_env_var(char *args)
{
    int j;
    j=0;
    // char *ev_name;
    // char *ev_value;

    printf("END VAR EXP : %s\n", args);
    printf("END VAR ARGS next : %s\n", args);
    if(args[j])
    {
        if(!(args[j] == '_') && !(args[j] >= 'a' && args[j] <= 'z') \
            && !(args[j] >= 'A' && args[j] <= 'Z'))
        {
            printf("invalid argument\n");
            return (1);
        }
    }
    while(args[j])
    {
        if(args[j] == '=')
        {
            if(check_env_var(args, j) == 1)
            {
                printf("invalid argument\n");
                return(1);
            }
            else
            {
                printf("valid argument\n");
                return(0);
            }
        }
        j++;
    }
    return (0);

}

static size_t find_export_index(char *s1, char *s2) 
{
    if (*s2 == '\0') {
        return (0);
    }
    size_t i = 0;
    size_t j = 0;
   // int index_export = 0;

    while (s1[i] != '\0') {

        while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i]) {
            i++;
            j++;
        }

        if (s2[j] == '\0') {
            return (i);
        }

        s1++;
    }
    return (0);
}

void    ft_export(t_shell *var, char *args)
{
    int     i;
    size_t     index_var;
    char **tmp;

    i = 1;

    i = i;
    tmp = NULL;
    tmp = tmp;
    var = var;
    args = args;
    index_var = find_export_index(args, "export ");
    //printf("EXPORT : %s\n", args[i]);

    if(valid_env_var(args + index_var) == 0)
    {
        printf("valiidddd\n");
        //add to env
    }
    else
        printf("invalid\n");

    // while (args[i])
    // {
    //     if ((ft_strncmp(args[i], "export\0", 7)))
    //     {
    //         if(valid_env_var(args, i + 1) == 0)
    //             printf("validdd\n");
    //             //add_to_env(args, index);
    //     }
    //     i++;
    // }
    // return ;
}