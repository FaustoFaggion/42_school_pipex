#include "pipex.h"

void	print_split(char **ptr)
{
	int	i;

	i = 0;
	while (ptr[i])
	{
		printf("%s\n", ptr[i]);
		i++;
	}
}

void	print_join(char *str)
{
		printf("%s\n", str);
}