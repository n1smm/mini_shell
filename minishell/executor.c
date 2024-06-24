#include "minishell.h"

void	ft_executor(t_token **token)
{
	printf("FT_EXECUTOR\n");
	if(!token)
		return ;
	while (*token)
	{
		//printf("%s\n", (*token)->content);
		//printf("%d\n", (*token)->typ_token);
		if((*token)->typ_token == COMMAND)
		{
			printf("%s\n", (*token)->content);
			if (ft_strncmp((*token)->content, "ls", 3) == 0)
				ft_ls();
			else if(ft_strncmp((*token)->content, "env", 3) == 0)
				ft_env();
			else if(ft_strncmp((*token)->content, "pwd", 3) == 0)
				ft_pwd();
			else if(ft_strncmp((*token)->content, "echo", 4) == 0)
			{
				//printf("ECHO\n");
				printf("%s\n", (*token)->next->next->content);
				ft_echo((*token)->next->next->content);
			}
			else
				printf("\nnull\n");
		}
		(*token) = (*token)->next;
	}
}