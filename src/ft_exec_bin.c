/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exec_bin.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:20:50 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/29 09:46:24 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_find_path(t_env **lst)
{
	while (*lst)
	{
		if (ft_strcmp((*lst)->name, "PATH") == 0)
			return ;
		(*lst) = (*lst)->next;
	}
}

char	*ft_next_path(char *path, char *cmd, int *i)
{
	char	*new_path;
	int		j;
	int		cpy_i;

	j = 0;
	cpy_i = *i;
	new_path = NULL;
	while (path[*i] && path[*i] != ':')
	{
		j++;
		(*i)++;
	}
	if (!(new_path = malloc(sizeof(char) * j + 2)))
		exit(-1);
	j = 0;
	while (path[cpy_i] && path[cpy_i] != ':')
		new_path[j++] = path[cpy_i++];
	new_path[j++] = '/';
	new_path[j] = '\0';
	new_path = ft_strjoin(new_path, cmd, 1);
	if (path[*i] == ':')
		(*i)++;
	return (new_path);
}

void	ft_exec_bin(t_minishell *st, t_env **lst)
{
	char	*cpy;
	int		ret;
	t_env	*cpy_lst;
	int		i;

	cpy = NULL;
	i = 0;
	cpy_lst = (*lst);
	ret = -1;
	ft_find_path(lst);
	while ((*lst) && (*lst)->path[i] && ret == -1)
	{
		if (cpy)
			free(cpy);
		cpy = ft_next_path((*lst)->path, st->arg[0], &i);
		ret = execve(cpy, st->arg, st->env);
	}
	(*lst) = cpy_lst;
	if (ret == -1)
		ret = execve(st->arg[0], st->arg, st->env);
	if (ret == -1)
		ft_error_bin(st);
	free(cpy);
}
