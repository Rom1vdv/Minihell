#include "../Includes/minishell.h"

void	*ft_malloc(int size, char *msg) //add header
{
	void	*res;

	res = malloc(size);
	if (!res)
		ft_perror(msg);
	return (res);
}
