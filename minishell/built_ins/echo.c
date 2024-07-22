/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tjuvan <tjuvan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/21 12:15:08 by thiew             #+#    #+#             */
/*   Updated: 2024/07/18 19:09:07 by tjuvan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

void ft_echo(char **args)
{
    int i = 1;
    int n_flag = 0;

    if (args[i] == NULL) {
        printf("\n");
        return;
    }
    while (args[i] && strcmp(args[i], "-n") == 0) {
        n_flag = 1;
        i++;
    }
    while (args[i]) {
        printf("%s", args[i]);
        if (args[i + 1]) {
            printf(" ");
        }
        i++;
    }

    if (n_flag == 0) {
        printf("\n");
    }
}
