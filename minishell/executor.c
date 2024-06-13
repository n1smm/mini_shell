#include "minishell.h"

void	ft_executor(t_token **token)
{
	if(!token)
		return ;
	while (token)
	{
		if((*token)->typ_token == COMMAND)
		{
			if(ft_strncmp((*token)->content, "env", 3) == 0)
				ft_env();
			else if(ft_strncmp((*token)->content, "pwd", 3) == 0)
				ft_pwd();
			else if(ft_strncmp((*token)->content, "echo", 5) == 0)
				ft_env();
			else
				printf("\nnull\n");
		}
		else
			return ;
		(*token) = (*token)->next;
	}
}