#include "minishell.h"

// void ft_ls(void)
// {
// 	DIR *dir;
// 	struct dirent *folder;
// 	char *directory;
// 	char pwd[1024];

// 	printf("%s\n", getcwd(pwd, sizeof(pwd)));
// 	//pwd = ft_strdup(getcwd(pwd, sizeof(pwd)));
// 	directory = pwd;
// 	dir = opendir(directory);
// 	if(!dir)
// 		exit(EXIT_FAILURE);
// 	while((folder = readdir(dir)))
// 		printf("%s\n", folder->d_name);
// 	if(closedir(dir) == -1)
// 		exit(EXIT_FAILURE);
// }