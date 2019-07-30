/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_minishell.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 09:58:02 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/31 18:07:41 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_second_processe(t_minishell *st, t_env **lst)
{
	int		i;

	g_pid = fork();
	if (g_pid > 0)
		waitpid(-1, &i, 0);
	if (g_pid == 0)
	{
		ft_exec_bin(st, lst);
		exit(0);
	}
}

void	ft_free_stru(t_minishell *st, t_env **lst, int s1)
{
	int		i;
	t_env	*cpy;

	cpy = (*lst);
	i = 0;
	st->builtins = 0;
	st->quote = 0;
	free((char*)st->tmp);
	while (st->arg[i])
		free(st->arg[i++]);
	free(st->arg);
	if (s1 && (*lst))
	{
		i = 0;
		while (*lst)
		{
			free((*lst)->name);
			free((*lst)->path);
			cpy = (*lst)->next;
			free(*lst);
			(*lst) = cpy;
		}
		ft_free_env(st);
	}
}

int		ft_find_cmd(t_minishell *st, t_env **lst)
{
	int		i;

	i = 0;
	if ((ft_strcmp(st->arg[0], "exit")) == 0)
	{
		if (st->arg[1])
			i = ft_atoi(st->arg[1]);
		ft_free_stru(st, lst, 1);
		exit(i);
	}
	else if ((ft_strcmp(st->arg[0], "cd")) == 0)
		st->builtins += CD;
	else if ((ft_strcmp(st->arg[0], "echo")) == 0)
		st->builtins += ECHO;
	else if ((ft_strcmp(st->arg[0], "env")) == 0)
		st->builtins += ENV;
	else if ((ft_strcmp(st->arg[0], "setenv")) == 0)
		st->builtins += SETENV;
	else if ((ft_strcmp(st->arg[0], "unsetenv")) == 0)
		st->builtins += UNSETENV;
	if ((*st).builtins)
		return (1);
	else
		return (0);
}

void	ft_minishell(t_minishell *st, t_env **lst)
{
	st->builtins = 0;
	ft_split_shell(st);
	if (*lst)
		ft_env(st, lst);
	if (ft_find_cmd(st, lst))
		ft_find_built(st, lst);
	else
		ft_second_processe(st, lst);
	ft_free_stru(st, lst, 0);
}
