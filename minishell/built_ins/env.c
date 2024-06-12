#include "../minishell.h"

bool	env(void)
{
	char	env[1024];

	if (getenv(env) != NULL)
	{
		printf("env: %s\n", env);
		return (true);
	}
	else
	{
		printf("env error\n");
		return (false);
	}
}