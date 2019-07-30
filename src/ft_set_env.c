/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_set_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 09:50:40 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/25 07:56:16 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_write_env(t_env **lst, char *path)
{
	int		j;
	int		i;

	i = 0;
	j = 0;
	while (path[j] != '=')
		j++;
	if (!((*lst)->name = malloc(sizeof(char) * j + 1)))
		exit(-1);
	while (path[j + i])
		i++;
	if (!((*lst)->path = malloc(sizeof(char) * i + 1)))
		exit(-1);
	i = -1;
	while (path[++i] != '=')
		(*lst)->name[i] = path[i];
	(*lst)->name[i++] = '\0';
	j = 0;
	while (path[i])
		(*lst)->path[j++] = path[i++];
	(*lst)->path[j] = '\0';
}

void	ft_prepare_env(t_env **lst, char *path, int s1)
{
	if (s1 && *lst)
	{
		while ((*lst)->next)
			(*lst) = (*lst)->next;
		(*lst)->next = ft_lst_init((*lst));
		(*lst)->next->prev = (*lst);
		(*lst) = (*lst)->next;
	}
	else if (!(*lst) && s1)
	{
		*lst = ft_lst_init(NULL);
		(*lst)->next = NULL;
	}
	else
	{
		free((*lst)->name);
		free((*lst)->path);
	}
	ft_write_env(lst, path);
}

void	ft_find_set_env(t_env **lst, char *env_name)
{
	while (*lst)
	{
		if (ft_strcmp((*lst)->name, env_name) == 0)
			break ;
		*lst = (*lst)->next;
	}
}

void	ft_find_name(t_env **lst, char *path)
{
	char	*cpy;
	int		i;
	t_env	*cpy_lst;

	cpy_lst = *lst;
	i = 0;
	while (path[i] != '=')
		i++;
	if (!(cpy = malloc(sizeof(char) * (i + 1))))
		exit(-1);
	i = -1;
	while (path[++i] != '=')
		cpy[i] = path[i];
	cpy[i] = '\0';
	ft_find_set_env(lst, cpy);
	free(cpy);
	if (*lst)
		ft_prepare_env(lst, path, 0);
	else
	{
		*lst = cpy_lst;
		ft_prepare_env(lst, path, 1);
	}
}

void	ft_set_env(t_minishell *st, t_env **lst)
{
	int		i;
	int		j;

	i = 1;
	while (st->arg[i])
	{
		j = 1;
		while (st->arg[i][j] && st->arg[i][j - 1])
		{
			if (st->arg[i][j - 1] != ' ' && st->arg[i][j - 1] != '\t'
					&& st->arg[i][j] == '=' && st->arg[i][j + 1] != ' ')
			{
				ft_find_name(lst, st->arg[i]);
				break ;
			}
			j++;
		}
		i++;
	}
	while ((*lst)->prev)
		(*lst) = (*lst)->prev;
	ft_cpy_env_st(st, lst);
}
