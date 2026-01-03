#include "minishell.h"
#include "libft.h"

/*
** Create a new env node
*/
static t_env	*env_new(char *key, char *value)
{
	t_env	*new;

	new = malloc(sizeof(t_env));
	if (!new)
		return (NULL);
	new->key = ft_strdup(key);
	new->value = ft_strdup(value);
	new->next = NULL;
	return (new);
}

/*
** Initialize env list from envp
*/
t_env	*env_init(char **envp)
{
	t_env	*env;
	t_env	*last;
	char	*eq;
	int		i;

	env = NULL;
	last = NULL;
	i = 0;
	while (envp[i])
	{
		eq = ft_strchr(envp[i], '=');
		if (eq)
		{
			t_env *node = env_new(
				ft_substr(envp[i], 0, eq - envp[i]),
				eq + 1);
			if (!env)
				env = node;
			else
				last->next = node;
			last = node;
		}
		i++;
	}
	return (env);
}

/*
** Get environment variable value
*/
char	*env_get(t_env *env, char *key)
{
	while (env)
	{
		if (!ft_strcmp(env->key, key))
			return (env->value);
		env = env->next;
	}
	return (NULL);
}

/*
** Set or update environment variable
*/
void	env_set(t_env **env, char *key, char *value)
{
	t_env	*tmp;

	tmp = *env;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			free(tmp->value);
			tmp->value = ft_strdup(value);
			return ;
		}
		tmp = tmp->next;
	}
	tmp = env_new(key, value);
	tmp->next = *env;
	*env = tmp;
}

/*
** Remove environment variable
*/
void	env_unset(t_env **env, char *key)
{
	t_env	*tmp;
	t_env	*prev;

	tmp = *env;
	prev = NULL;
	while (tmp)
	{
		if (!ft_strcmp(tmp->key, key))
		{
			if (prev)
				prev->next = tmp->next;
			else
				*env = tmp->next;
			free(tmp->key);
			free(tmp->value);
			free(tmp);
			return ;
		}
		prev = tmp;
		tmp = tmp->next;
	}
}
