
#include "../include/philosophers.h"

void	print_error_parse(char *begin, int i, char *end)
{
	char	*index;

	index = ft_itoa(i);
	ft_putstr_fd(begin, 2);
	write(2, index, 1);
	ft_putstr_fd(end, 2);
	free(index);
}

/*
size_t	ft_arraylen(char **array)
{
	size_t	len;
	int		i;

	i = 0;
	while (array[i])
	{
		len++;
		i++;
	}
	return (len);
}
*/
