#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

int main(int argc, char **argv)
{
	char *result;

	if (argc > 2)
		return 1;

	result = getenv("PATH");
	puts(result);
}
	
