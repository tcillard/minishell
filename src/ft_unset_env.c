/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset_env.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 16:40:00 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/29 16:01:19 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_free_env(t_minishell *st)
{
	int		i;

	i = 0;
	while (st->env[i])
		free(st->env[i++]);
	free(st->env);
}

int		ft_find_unset_env(t_env **lst, char *arg)
{
	t_env	*cpy;

	cpy = *lst;
	while (*lst)
	{
		if (ft_strcmp((*lst)->name, arg) == 0)
			return (1);
		(*lst) = (*lst)->next;
	}
	*lst = cpy;
	return (0);
}

void	ft_del_env(t_env **first, t_env **lst, t_minishell *st)
{
	t_env		*c;

	c = *lst;
	if ((*lst)->next)
		(*lst)->next->prev = (*lst)->prev;
	if ((*lst)->prev)
		(*lst)->prev->next = (*lst)->next;
	else if ((*lst)->next)
		(*lst) = (*lst)->next;
	if (c)
	{
		free(c->name);
		free(c->path);
		free(c);
	}
	ft_cpy_env_st(st, first);
}

void	ft_unset_env(t_minishell *st, t_env **lst)
{
	int		i;
	t_env	*cpy;

	cpy = *lst;
	i = 1;
	while (st->arg[i])
	{
		(*lst) = cpy;
		if (ft_find_unset_env(lst, st->arg[i]))
		{
			if (!(*lst)->prev)
				cpy = (*lst)->next;
			ft_del_env(&cpy, lst, st);
		}
		i++;
	}
	(*lst) = cpy;
}
