#include "minishell.h"
#include "libft/libft.h"

// void ft_parsing(char *input)
// {
// 	//
// }


void ft_init(t_input *commands)
{
	commands = commands;
	commands = (t_input*)safe_malloc(sizeof(t_input));

}


static char *prompt_check(void)
{
	char 	*cwd;
	char	*prompt;
	char	*user;

	user = expander("USER", EXPAND);
	cwd = safe_malloc(1024);
	if (getcwd(cwd, 1024) != NULL && user != NULL)
	{
		user = join_wrapper("Minishell-", user, 2);
		user = join_wrapper(user, ": ", 1);
		cwd = join_wrapper(user, cwd, 3);
		prompt = join_wrapper(cwd, "$ ", 1);
	}
	else
	{
		free(cwd);
		free(user);
		prompt = strdup("Minishell$:");
	}
	return (prompt);
}

int main()
{
	char	*input;
	char	*prompt;
//	t_input *commands;
	while(1)
	{
		prompt = prompt_check();
		input = readline(prompt);
		add_history(input);
		//ft_parsing(input);
		//printf("\n");
		split_input(input);
		//ft_lexer(input);
		if (ft_strncmp(input, "exit", 5) == 0)
		 	break;
		free(input);
		free(prompt);
	}
	free(input);
	free(prompt);
	return(0);
}
