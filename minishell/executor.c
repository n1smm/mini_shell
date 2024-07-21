#include "minishell.h"

void	ft_executor(t_shell *data, t_token **token, char *args, char **env)
{
	t_token	*curr;
	env = env;
	char **test;

	test = safe_malloc(sizeof(char *) * 2 + 1);
	test[0] = ft_strdup("export");
	test[1] = ft_strdup("USER=mon");
	test[2] = NULL;

	if(!data)
		return ;
	// init_env_vars(tail, head);
	args = args;
	curr = *token;
	while (curr)
	{
		//printf("%s\n", (*token)->content);
		//printf("%d\n", (*token)->typ_token);
		if(curr->typ_token == COMMAND)
		{
			printf("%s\n", curr->content);
			if (ft_strncmp(curr->content, "ls", 3) == 0)
				ft_ls();
			else if(ft_strncmp(curr->content, "env", 3) == 0)
				ft_env(data);
			else if(ft_strncmp(curr->content, "export", 6) == 0)
				ft_export(data, test);
				/* ft_export(var, env); */
			else if(ft_strncmp(curr->content, "pwd", 3) == 0)
				ft_pwd();
			else if(ft_strncmp(curr->content, "echo", 4) == 0)
			{
				;//ft_echo(args);
			}
			else
				printf("\nnull\n");
		}
		curr = curr->next;
	}
}
