#include "minishell.h"
#include "libft.h"


void	prompt_loop(t_env **env)
{
	char	*line;
	char	**args;

	while (1)
	{
		line = readline("minishell$ ");
		if (!line)
		{
			free_env(*env);
			exit(0);
		}
		if (*line)
			add_history(line);
		args = lexer(line);
		free(line);
		if (args)
		{
			execute(args, env);
			free_args(args);
		}
	}
}




// int	prompt_loop(t_env **env)
// {
// 	char	*line;
// 	char	**args;
// 	int		status;

// 	status = 0;
// 	while (1)
// 	{
// 		line = readline("minishell$ ");
// 		if (!line)
// 			exit(status);
// 		if (is_empty(line))
// 		{
// 			free(line);
// 			continue ;
// 		}
// 		add_history(line);
// 		args = lexer(line);
// 		free(line);
// 		if (!parser(args))
// 			status = execute(args, env);
// 		free_args(args);
// 	}
// }
