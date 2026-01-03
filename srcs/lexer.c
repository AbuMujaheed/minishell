#include "minishell.h"
#include "libft.h"

char	**lexer(char *line)
{
	char	**args;
	int		i;

	args = ft_split(line, ' ');
	i = 0;
	while (args[i])
		i++;
	return (args);
}
