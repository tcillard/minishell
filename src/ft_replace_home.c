/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_replace_home.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/29 09:54:39 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/30 18:10:52 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_insert_home_cd(t_minishell *st)
{
	free(st->arg[0]);
	free(st->arg[1]);
	free(st->arg);
	if (!(st->arg = malloc(sizeof(char*) * 3)))
		exit(-1);
	st->arg[0] = ft_strdup("cd");
	st->arg[1] = ft_strdup("/Users/tcillard");
	st->arg[2] = NULL;
}

int		ft_find_env_cd(t_env **lst)
{
	while (*lst && (ft_strcmp("OLDPWD", (*lst)->name)) != 0)
		(*lst) = (*lst)->next;
	if (*lst)
		return (1);
	else
		return (0);
}

void	ft_replace_home(t_minishell *st, t_env **lst, int i)
{
	t_env	*cpy;

	cpy = (*lst);
	while ((*lst) && ft_strcmp("HOME", (*lst)->name) != 0)
		(*lst) = (*lst)->next;
	if (!(*lst))
	{
		(*lst) = cpy;
		return ;
	}
	free(st->arg[i]);
	st->arg[i] = ft_strdup((*lst)->path);
	(*lst) = cpy;
}
