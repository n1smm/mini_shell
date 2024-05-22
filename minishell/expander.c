/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:49:11 by thiew             #+#    #+#             */
/*   Updated: 2024/05/22 13:24:19 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* if the type of token is correct it will allocate, otherwise it returns null not allocated */
char	*expander(char *input, t_type typ_token)
{
	char *result;
	char *result_path;

	if (typ_token == COMMAND)
	{
		result = path_finder(input);
		if (!result)
			return (NULL);
		return (result);


	}
	else if (typ_token == EXPAND)
	{
		result = getenv(input);
		result_path = ft_strdup(result);
		return (result_path);
	}
	return (NULL);
}

int main(int argc, char **argv)
{
	if (argc > 3)
		return 0;
	char *input;
	char *input2;

	input = expander(argv[1], COMMAND);
	input2 = expander(argv[2], EXPAND);
	if (!input || !input2)
	{
		printf("not a valid input");
		return 1;
	}
	printf("command is: %s\n", input);
	printf("path is: %s\n", input2);
	free(input);
	free(input2);
}
