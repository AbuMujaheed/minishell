#include "minishell.h"
#include "libft.h"

#include "minishell.h"

/*
** Check if command is a builtin
*/
int	is_builtin(char *cmd)
{
	if (!cmd)
		return (0);
	if (!ft_strcmp(cmd, "echo"))
		return (1);
	if (!ft_strcmp(cmd, "cd"))
		return (1);
	if (!ft_strcmp(cmd, "pwd"))
		return (1);
	if (!ft_strcmp(cmd, "env"))
		return (1);
	if (!ft_strcmp(cmd, "export"))
		return (1);
	if (!ft_strcmp(cmd, "unset"))
		return (1);
	if (!ft_strcmp(cmd, "exit"))
		return (1);
	return (0);
}

/*
** echo builtin
*/
static int	builtin_echo(char **argv)
{
	int	i;
	int	nl;

	i = 1;
	nl = 1;
	if (argv[1] && !ft_strcmp(argv[1], "-n"))
	{
		nl = 0;
		i++;
	}
	while (argv[i])
	{
		write(1, argv[i], ft_strlen(argv[i]));
		if (argv[i + 1])
			write(1, " ", 1);
		i++;
	}
	if (nl)
		write(1, "\n", 1);
	return (0);
}

/*
** pwd builtin
*/
static int	builtin_pwd(void)
{
	char	cwd[4096];

	if (!getcwd(cwd, sizeof(cwd)))
		return (1);
	write(1, cwd, ft_strlen(cwd));
	write(1, "\n", 1);
	return (0);
}

/*
** env builtin
*/
static int	builtin_env(t_env *env)
{
	while (env)
	{
		if (env->value)
		{
			write(1, env->key, ft_strlen(env->key));
			write(1, "=", 1);
			write(1, env->value, ft_strlen(env->value));
			write(1, "\n", 1);
		}
		env = env->next;
	}
	return (0);
}

/*
** cd builtin
*/
static int	builtin_cd(char **argv, t_env **env)
{
	char	*path;

	(void)env;
	if (!argv[1])
		path = env_get(*env, "HOME");
	else
		path = argv[1];
	if (!path || chdir(path) != 0)
	{
		write(2, "cd: error\n", 10);
		return (1);
	}
	return (0);
}

/*
** export builtin
*/
static int	builtin_export(char **argv, t_env **env)
{
	int		i;
	char	*eq;

	i = 1;
	while (argv[i])
	{
		eq = ft_strchr(argv[i], '=');
		if (eq)
		{
			*eq = '\0';
			env_set(env, argv[i], eq + 1);
			*eq = '=';
		}
		i++;
	}
	return (0);
}

/*
** unset builtin
*/
static int	builtin_unset(char **argv, t_env **env)
{
	int	i;

	i = 1;
	while (argv[i])
	{
		env_unset(env, argv[i]);
		i++;
	}
	return (0);
}

/*
** exit builtin
*/
static int	builtin_exit(char **argv)
{
	int	status;

	status = 0;
	if (argv[1])
		status = ft_atoi(argv[1]);
	write(1, "exit\n", 5);
	exit(status);
}

/*
** Execute builtin
*/
int	run_builtin(char **argv, t_env **env)
{
	if (!ft_strcmp(argv[0], "echo"))
		return (builtin_echo(argv));
	if (!ft_strcmp(argv[0], "cd"))
		return (builtin_cd(argv, env));
	if (!ft_strcmp(argv[0], "pwd"))
		return (builtin_pwd());
	if (!ft_strcmp(argv[0], "env"))
		return (builtin_env(*env));
	if (!ft_strcmp(argv[0], "export"))
		return (builtin_export(argv, env));
	if (!ft_strcmp(argv[0], "unset"))
		return (builtin_unset(argv, env));
	if (!ft_strcmp(argv[0], "exit"))
		return (builtin_exit(argv));
	return (1);
}

