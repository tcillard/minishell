/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env_base.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:54:19 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/30 17:38:44 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_get_pwd(void)
{
	int		i;
	char	*pwd;
	char	*cpy;

	i = 1;
	if (!(pwd = malloc(i)))
		exit(-1);
	cpy = pwd;
	while ((pwd = getcwd(pwd, i)) == NULL)
	{
		i++;
		free(cpy);
		if (i == 2000)
		{
			cpy = ft_strdup("");
			break ;
		}
		if (!(pwd = malloc(i)))
			exit(-1);
		cpy = pwd;
	}
	return (cpy);
}

void	ft_creat_pwd(t_env **lst)
{
	(*lst) = ft_lst_init(NULL);
	(*lst)->name = ft_strdup("PWD");
	(*lst)->path = ft_get_pwd();
}

void	ft_new_pwd(t_env **lst)
{
	t_env	*cpy;

	cpy = (*lst);
	if (!(*lst))
	{
		ft_creat_pwd(lst);
		return ;
	}
	while ((*lst)->next && ft_strcmp("PWD", (*lst)->name) != 0)
		(*lst) = (*lst)->next;
	if (ft_strcmp((*lst)->name, "PWD") != 0)
	{
		(*lst)->next = ft_lst_init(*lst);
		(*lst) = (*lst)->next;
		(*lst)->name = ft_strdup("PWD");
		(*lst)->path = ft_get_pwd();
		(*lst) = cpy;
	}
	else
	{
		free((*lst)->path);
		(*lst)->path = ft_get_pwd();
		(*lst) = cpy;
	}
}

void	ft_env_base(t_env **lst, t_minishell *st)
{
	*lst = ft_lst_init(NULL);
	(*lst)->name = ft_strdup("PWD");
	(*lst)->path = ft_get_pwd();
	(*lst)->next = ft_lst_init(*lst);
	(*lst) = (*lst)->next;
	(*lst)->name = ft_strdup("SHLVL");
	(*lst)->path = ft_strdup("1");
	(*lst)->next = ft_lst_init(*lst);
	(*lst) = (*lst)->next;
	(*lst)->name = ft_strdup("_");
	(*lst)->path = ft_strdup("/usr/bin/env");
	while ((*lst)->prev)
		(*lst) = (*lst)->prev;
	ft_cpy_env_st(st, lst);
}

void	ft_shlvl(t_env **lst, char *env)
{
	int		i;
	int		j;
	int		lvl;

	i = 0;
	j = 0;
	lvl = 0;
	free((*lst)->path);
	(*lst)->path = NULL;
	while (env[i] != '=')
		i++;
	i++;
	while (env[i])
		lvl = (lvl * 10) + (env[i++] - '0');
	lvl++;
	(*lst)->path = ft_itoa(lvl);
}
