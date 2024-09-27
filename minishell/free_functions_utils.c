#include "minishell.h"

void	free_mtx(void **matrix)
{
	int	i;

	i = 0;
	if (matrix == NULL)
		return ;
	while (matrix[i])
		free(matrix[i++]);
	free(matrix);
}

void	error_handling(char *msg, int error_code)
{
	perror(msg);
	g_error_code = error_code;
}
