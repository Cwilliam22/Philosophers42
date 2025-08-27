
#include "../include/philosophers.h"

void	print_error_parse(char *begin, char *end, int i)
{
	char	*index;

	index = ft_itoa(i);
	ft_putstr_fd(begin, 2);
	write(2, index, 1);
	ft_putstr_fd(begin, 2);
	free(index);
}
