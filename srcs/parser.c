#include "minishell.h"
#include "libft.h"
/*
** Returns 0 if syntax is valid
** Returns 1 if syntax error
**
** For the current project base, we reject:
** - NULL args
** - empty command
**
** Pipes and redirections will be handled later
*/
int	parser(char **args)
{
	if (!args || !args[0])
		return (1);
	return (0);
}