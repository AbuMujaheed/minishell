#include "minishell.h"
#include "libft.h"
/*
** Frees the environment linked list
*/
void	free_env(t_env *env)
{
	t_env	*tmp;

	while (env)
	{
		tmp = env->next;
		free(env->key);
		free(env->value);
		free(env);
		env = tmp;
	}
}

/*
** Frees a single string safely
*/
void	free_str(char **s)
{
	if (!s || !*s)
		return ;
	free(*s);
	*s = NULL;
}
