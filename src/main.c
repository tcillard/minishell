/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 09:44:06 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/29 16:29:33 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_init_struct(t_minishell *st, t_env **lst)
{
	(*lst) = NULL;
	st->arg = NULL;
	st->builtins = 0;
	st->quote = 0;
	st->tmp = NULL;
	st->env = NULL;
}

int		ft_end_cmd(t_minishell *st, char *buff)
{
	int		i;

	i = 0;
	while (buff[i] && (buff[i] != '\n' || (*st).quote))
	{
		ft_quote(buff[i], st);
		i++;
	}
	if ((*st).quote)
	{
		ft_putstr("quote>");
		return (0);
	}
	else if (buff[i] == '\n' && !(*st).quote)
		return (1);
	return (0);
}

void	ft_new_cmd(t_minishell *st)
{
	g_pid = 0;
	signal(SIGINT, ft_kill);
	st->tmp = ft_strdup("\0");
	ft_putstr("$>");
}

int		ft_check_cmd(t_minishell *st)
{
	int	i;

	i = 0;
	while (st->tmp[i] == ' ' || st->tmp[i] == '\t'
			|| st->tmp[i] == '\n')
		i++;
	if (!(st->tmp[i]))
	{
		free((char*)st->tmp);
		return (0);
	}
	else
		return (1);
}

int		main(int ac, char **av, char **env)
{
	char		buff[BUFFER_SIZE];
	t_minishell	st;
	int			ret;
	t_env		*lst;

	(void)ac;
	(void)av;
	ft_init_struct(&st, &lst);
	ft_creat_lst_env(&lst, &st, env);
	ret = 0;
	while (42)
	{
		ft_bzero((char*)buff, BUFFER_SIZE);
		ft_new_cmd(&st);
		while (!(ft_end_cmd(&st, buff)))
		{
			ret = read(0, buff, BUFFER_SIZE);
			buff[ret] = '\0';
			st.tmp = ft_strjoin(st.tmp, (const char*)buff, 1);
		}
		if (ft_check_cmd(&st))
			ft_minishell(&st, &lst);
	}
	return (0);
}
