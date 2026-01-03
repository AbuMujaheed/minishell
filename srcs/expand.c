#include "minishell.h"
#include "libft.h"

static char	*get_var_name(char *s, int *i)
{
	int		start;
	char	*name;

	start = *i;
	while (s[*i] && (ft_isalnum(s[*i]) || s[*i] == '_'))
		(*i)++;
	name = ft_substr(s, start, *i - start);
	return (name);
}

static char	*expand_one(char *arg, t_env *env, int last_status)
{
	char	*res;
	char	*tmp;
	char	*value;
	char	*name;
	int		i;

	res = ft_strdup("");
	i = 0;
	while (arg[i])
	{
		if (arg[i] == '$' && arg[i + 1])
		{
			i++;
			if (arg[i] == '?')
			{
				value = ft_itoa(last_status);
				i++;
			}
			else
			{
				name = get_var_name(arg, &i);
				value = env_get(env, name);
				free(name);
				if (!value)
					value = "";
			}
			tmp = res;
			res = ft_strjoin(tmp, value);
			free(tmp);
			if (arg[i - 1] == '?' || value[0])
				free(value);
		}
		else
		{
			tmp = res;
			res = ft_strjoin_char(tmp, arg[i]);
			free(tmp);
			i++;
		}
	}
	return (res);
}

void	expand_vars(char **args, t_env *env, int last_status)
{
	int		i;
	char	*new;

	i = 0;
	while (args[i])
	{
		if (ft_strchr(args[i], '$'))
		{
			new = expand_one(args[i], env, last_status);
			free(args[i]);
			args[i] = new;
		}
		i++;
	}
}
