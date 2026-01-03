#include "minishell.h"

volatile sig_atomic_t	g_sig;

int	main(int ac, char **av, char **envp)
{
	t_env	*env;

	(void)ac;
	(void)av;
	env = env_init(envp);
	init_signals();
	prompt_loop(&env);
	return (0);
}
