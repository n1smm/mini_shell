#include "minishell.h"

void *safe_malloc(size_t size)
{
	void *ptr = malloc(size);
	if (!ptr)
	{
		perror("Malloc failed");
		return (NULL);
	}
	return (ptr);
}