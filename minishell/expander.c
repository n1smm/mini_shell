/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expander.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: thiew <marvin@42.fr>                       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 15:49:11 by thiew             #+#    #+#             */
/*   Updated: 2024/05/30 23:29:19 by thiew            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

char	*refactor_expanded_string(char *content, int start, int len)
{
	char	*expanded;
	char	*result;
	char	*contentcpy;

	expanded = ft_substr(content, start, len);
	result = expander(expanded, EXPAND);
	free(expanded);
	expanded = ft_strdup(content + (start + len));
	contentcpy = ft_substr(content, 0, start - 1);
	result = join_wrapper(contentcpy, result, 2);
	result = join_wrapper(result, expanded, 3);
	return (result);
}

void	refurbish_node(t_token *curr, char *content)
{
	int		i;
	bool	path;

	i = 0;
	path = false;
	curr->typ_token = WORD;
	while (content[i])
	{
		if (!ft_isalpha(content[i]))
			curr->typ_token = STRING;	
		if (content[i++] == '/')
			path = true;
	}
	if (path)
		curr->typ_token = PATH;
	curr->content = content;
}

void	expand_checker(t_token *curr)
{
	char	*expand;
	char	*content;
	int		i;
	int		j;

	i = 0;
	j = 0;
	content = curr->content;
	
	while (content[i] != '$' && content[i] != 0)
		i++;
	++i;
	while (content[j] != 0 && (ft_isalnum(content[j]) || content[j] == '_'))
		j++;
	content = refactor_expanded_string(content, i, j - 1);
	refurbish_node(curr, content);

	
}

/* int main(int argc, char **argv) */
/* { */
/* 	if (argc > 3) */
/* 		return 0; */
/* 	char *input; */
/* 	char *input2; */

/* 	t_token *curr = { */
/* 	input = expander(argv[1], COMMAND); */
/* 	input2 = expander(argv[2], EXPAND); */
/* 	if (!input || !input2) */
/* 	{ */
/* 		printf("not a valid input"); */
/* 		return 1; */
/* 	} */
/* 	printf("command is: %s\n", input); */
/* 	printf("path is: %s\n", input2); */
/* 	free(input); */
/* 	free(input2); */
/* } */

void print_tokens(t_token *head)
{
    t_token *curr = head;
    while (curr)
    {
        printf("Token: %s, Type: %d\n", curr->content, curr->typ_token);
        curr = curr->next;
    }
}

int main()
{
    // Create tokens
    t_token token1 = {WORD, "ls", NULL, NULL};
    t_token token2 = {STRING, "/etc/passwd", NULL, &token1};
    t_token token3 = {PIPELINE, "|", NULL, &token2};
    t_token token4 = {WORD, "echo", NULL, &token3};
    t_token token5 = {QUOTE, "\"", NULL, &token4};
    t_token token6 = {WORD, "hello", NULL, &token5};
    t_token token7 = {STRING, "hello$USER/mjuu", NULL, &token6};
    t_token token8 = {STRING, "/this/is/not/a/path", NULL, &token7};
    t_token token9 = {QUOTE, "\"", NULL, &token8};

    token1.next = &token2;
    token2.next = &token3;
    token3.next = &token4;
    token4.next = &token5;
    token5.next = &token6;
    token6.next = &token7;
    token7.next = &token8;
    token8.next = &token9;

    // Simulate expansion on token7 (with content "$USER")
    expand_checker(&token7);

    // Print tokens to see the results
    print_tokens(&token1);

    return 0;
}







