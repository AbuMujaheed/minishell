#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/wait.h>
# include <readline/readline.h>
# include <readline/history.h>



extern volatile sig_atomic_t	g_sig;

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;
}	t_env;

/* core */
void	prompt_loop(t_env **env);

/* lexer / parser */
char	**lexer(char *line);
int		parser(char **args);

/* execution */
int		execute(char **args, t_env **env);

/* builtins */
int		is_builtin(char *cmd);
int		run_builtin(char **args, t_env **env);

/* env */
t_env	*env_init(char **envp);
char	*env_get(t_env *env, char *key);
void	env_set(t_env **env, char *key, char *value);
void	env_unset(t_env **env, char *key);
void	free_env(t_env *env);


/* expand */
void	expand_vars(char **args, t_env *env, int last_status);

/* signals */
void	init_signals(void);

/* utils */
int		is_empty(char *s);
void	free_args(char **args);
char	*ft_strjoin_char(char *s, char c);
int		ft_strcmp(const char *s1, const char *s2);

#endif
