#include "minishell.h"

void	ft_executor(t_token **token, char **env)
{
	t_token	*curr;
	t_shell	*var;

	var->env = NULL;

	//printf("FT_EXECUTOR\n");
	if(!token || !*token)
		return ;
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
				ft_env(env);
			else if(ft_strncmp(curr->content, "export", 6) == 0)
				ft_export(var, env);
			else if(ft_strncmp(curr->content, "pwd", 3) == 0)
				ft_pwd();
			else if(ft_strncmp(curr->content, "echo", 4) == 0)
			{
				//printf("ECHO\n");
				printf("%s\n", curr->next->next->content);
				ft_echo(curr->next->next->content);
			}
			else
				printf("\nnull\n");
		}
		curr = curr->next;
	}
}