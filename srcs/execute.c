#include "minishell.h"
#include "libft.h"

static char	*find_path(char *cmd, t_env *env)
{
	char	*path;
	char	**dirs;
	int		i;

	if (access(cmd, X_OK) == 0)
		return (cmd);
	path = env_get(env, "PATH");
	if (!path)
		return (NULL);
	dirs = ft_split(path, ':');
	i = 0;
	while (dirs[i])
	{
		char *tmp = ft_strjoin(dirs[i], "/");
		char *full = ft_strjoin(tmp, cmd);
		free(tmp);
		if (access(full, X_OK) == 0)
			return (full);
		free(full);
		i++;
	}
	return (NULL);
}

int	execute(char **args, t_env **env)
{
	pid_t	pid;
	int		status;
	char	*cmd;

	if (!args[0])
		return (0);
	if (is_builtin(args[0]))
		return (run_builtin(args, env));
	pid = fork();
	if (pid == 0)
	{
		cmd = find_path(args[0], *env);
		if (!cmd)
			exit(127);
		execve(cmd, args, NULL);
		exit(1);
	}
	waitpid(pid, &status, 0);
	if (WIFEXITED(status))
		return (WEXITSTATUS(status));
	return (1);
}
