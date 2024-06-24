#include "minishell.h"

void ft_ls(void)
{
	DIR *dir;
	struct dirent *folder;
	char *directory;
	char *pwd;

	pwd = NULL;
	pwd = getcwd(pwd, sizeof(pwd));
	directory = pwd;
	dir = opendir(directory);
	if(!dir)
		exit(EXIT_FAILURE);
	while((folder = readdir(dir)))
		printf("%s\n", folder->d_name);
	if(closedir(dir) == -1)
		exit(EXIT_FAILURE);
}