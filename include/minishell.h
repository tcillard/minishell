/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/14 18:10:36 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/30 18:02:46 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define BUFFER_SIZE	1024
# define APOS			2
# define QUOTE			1
# define EXIT			32
# define ENV			16
# define UNSETENV		8
# define SETENV			4
# define ECHO			2
# define CD				1

# include "libft.h"
# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <sys/types.h>
# include <sys/time.h>
# include <sys/resource.h>
# include <sys/wait.h>
# include <stdlib.h>
# include <sys/stat.h>
# include <fcntl.h>

typedef struct	s_minishell
{
	char		**arg;
	int			builtins;
	int			quote;
	const char	*tmp;
	char		**env;
}				t_minishell;

typedef struct	s_env
{
	char			*name;
	char			*path;
	struct s_env	*next;
	struct s_env	*prev;
}				t_env;

int				g_pid;

int				ft_find_env_cd(t_env **lst);
void			ft_insert_home_cd(t_minishell *st);
void			ft_new_pwd(t_env **lst);
void			ft_env_base(t_env **lst, t_minishell *st);
void			ft_shlvl(t_env **lst, char *env);
void			ft_minishell(t_minishell *st, t_env **lst);
void			ft_exec_bin(t_minishell *st, t_env **lst);
void			ft_find_built(t_minishell *st, t_env **lst);
void			ft_error_bin(t_minishell *st);
void			ft_echo(t_minishell *st);
void			ft_split_shell(t_minishell *st);
void			ft_quote(char c, t_minishell *st);
void			ft_cd(t_minishell *st, t_env **lst);
void			ft_error_access(char *error);
void			ft_error_exist(char *error);
void			ft_error_file(char *error);
void			ft_putenv(t_minishell *st);
void			ft_creat_lst_env(t_env **lst, t_minishell *st, char **env);
char			*ft_replace_env(t_minishell *st, int n, int i);
void			ft_env(t_minishell *st, t_env **lst);
char			*ft_env_sub(t_minishell *st, int i, int n, char *path);
void			ft_set_env(t_minishell *st, t_env **lst);
void			ft_unset_env(t_minishell *st, t_env **lst);
void			ft_record_lst_env(t_env **lst, char *env);
t_env			*ft_lst_init(t_env *past);
void			ft_cpy_env_st(t_minishell *st, t_env **lst);
void			ft_free_env(t_minishell *st);
void			ft_kill(int sig);
void			ft_replace_home(t_minishell *st, t_env **lst, int i);

#endif
