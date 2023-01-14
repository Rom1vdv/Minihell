#include "../includes/minishell.h"

void	ft_perror(char *str) //add header
{
	perror(str);
	exit(EXIT_FAILURE);
}
