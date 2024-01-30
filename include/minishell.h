/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: erigolon <erigolon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/06/20 12:27:52 by vicrodri          #+#    #+#             */
/*   Updated: 2024/01/30 14:13:47 by erigolon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "../libft/libft.h"
# include <dirent.h>
# include "parser.h"
# include "color.h"
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <termios.h>
# include <limits.h>


# define READ_END 0
# define WRITE_END 1

typedef struct s_lexer	t_lexer;

typedef struct cmdlist
{
	char			**cmd;
	char			*path;
	char			*fd_in;
	char			*fd_out;
	int				i_fd_in;
	int				i_fd_out;
	int				append;
	struct cmdlist	*next;
	struct cmdlist	*prev;
}	t_cmdlist;

typedef struct envlist
{
	char			*env;
	char			*value;
	struct envlist	*next;
	struct envlist	*prev;

}	t_envlist;

typedef struct minishell
{
	struct cmdlist	*cmds;
	struct envlist	*envlist;
	struct envlist	*explist;
	int				num_com;
	int				exe;
	char			*line;
	char			**envp;
	char			**path;
	int				*pipe;
	pid_t			child_pid;
	unsigned char	exit_status;
	int				exit;
	t_lexer			*lexer;
}	t_minishell;


void		ft_handler(int signum);
void		free_str(char **str, int i);
void		free_envlst(t_envlist *envlst);
char		**ft_strddup(char **envp);
void		ft_exit(t_minishell *ms, char **nb);
t_envlist	*split_n_fill_env(t_envlist	*new_env, char *env);
void		ft_exit(t_minishell *ms, char **nb);
void		free_all(t_minishell *ms);
void		free_loop(t_minishell *g_ms, char *prompt, t_lexer *lex);
t_lexer		*lex_parser(t_minishell *ms, char *prompt);
t_cmdlist	*ft_cmdlstnew(void);
void		ft_cmdlstadd_back(t_cmdlist **cmdlst, t_cmdlist *add);
t_cmdlist	*ft_cmdlstlast(t_cmdlist *cmdlst);
void		ft_free_cmdlst(t_minishell	*ms);
t_envlist	*lstnew_env(char *env);
void		lstadd_back_env(t_envlist **envlst, t_envlist *new);
void		free_envlst(t_envlist *envlst);
t_envlist	*split_n_fill_env(t_envlist *envlst, char *env);
t_envlist	*env_list(char	**envp);
t_envlist	*check_env(char *env, t_envlist *explist);
void		sort_envlst(t_envlist **lst);
void		envlst_to_env(t_minishell *ms);
void		delete_env(t_envlist **lst);
int			ft_pwd(void);
void		ft_cd(t_minishell *ms, char *str);
void		ft_echo(char **str);
void		ft_export(t_minishell *ms, char **str);
void		ft_env(t_minishell *ms);
void		ft_unset(t_minishell *ms, char **str);
int			ft_is_builtin(t_minishell *ms, t_cmdlist *tmp);
void		ft_accept_redirections(t_minishell *ms, t_cmdlist *tmp);
t_envlist	*ft_getenv(char *str, t_envlist *lst);
void		ft_shlvl_update(t_minishell *ms);
void		exec(t_minishell *ms);
void		ft_dup(int in, int out);
void		ft_close_pipe(t_minishell *ms);
void		ft_get_path(t_minishell *ms, t_cmdlist *tmp);
void		ft_free_fork(t_minishell *ms);
int			ft_here_doc(char *limiter);
void		ft_error_exe(char **arg, char *msg, t_minishell *ms);
void		ft_error_file(char *file, t_minishell *ms);
void		ft_sigint_proc(int sig);
void		ft_signheredoc(int sig);
#endif