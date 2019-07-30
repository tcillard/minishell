/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/19 19:09:06 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/30 18:14:49 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_find_error_cd(char *path)
{
	struct stat	s;
	int			mode;

	mode = F_OK | X_OK;
	if (lstat(path, &s) == -1)
	{
		ft_error_exist(path);
		return (0);
	}
	if ((s.st_mode & S_IFDIR) != S_IFDIR)
	{
		ft_error_file(path);
		return (0);
	}
	if (access(path, mode) == -1)
	{
		ft_error_access(path);
		return (0);
	}
	return (1);
}

int		ft_file_error_cd(t_minishell *st)
{
	char	*path;
	int		i;

	i = 0;
	if (!(path = malloc(sizeof(char) * ft_strlen(st->arg[1]) + 1)))
		exit(-1);
	while (st->arg[1][i])
	{
		while (st->arg[1][i] && st->arg[1][i] != '\\')
		{
			path[i] = st->arg[1][i];
			i++;
		}
		path[i] = '\0';
		if (!(ft_find_error_cd(path)))
		{
			free(path);
			return (0);
		}
	}
	free(path);
	return (1);
}

void	ft_get_oldpwd(t_env **lst)
{
	int		i;
	char	*cpy;

	i = 1;
	(*lst)->path = ft_strdup("");
	cpy = (*lst)->path;
	while (((*lst)->path = getcwd((*lst)->path, i)) == NULL)
	{
		i++;
		free(cpy);
		if (i == 2000)
		{
			(*lst)->path = ft_strdup("");
			break ;
		}
		if (!((*lst)->path = malloc(i)))
			exit(-1);
		cpy = (*lst)->path;
	}
	while ((*lst)->prev)
		(*lst) = (*lst)->prev;
}

void	ft_new_oldpwd(t_env **lst)
{
	t_env	*cpy;
	int		i;

	i = 0;
	cpy = (*lst);
	while ((*lst) && ft_strcmp("OLDPWD", (*lst)->name) != 0)
		(*lst) = (*lst)->next;
	if (!(*lst))
	{
		(*lst) = cpy;
		if (*lst)
		{
			while ((*lst)->next)
				(*lst) = (*lst)->next;
			(*lst)->next = ft_lst_init(*lst);
			(*lst) = (*lst)->next;
		}
		else
			*lst = ft_lst_init(NULL);
		(*lst)->name = ft_strdup("OLDPWD");
	}
	else
		free((*lst)->path);
	ft_get_oldpwd(lst);
}

void	ft_cd(t_minishell *st, t_env **lst)
{
	t_env	*cpy;

	cpy = (*lst);
	if (st->arg[1] == NULL)
		ft_insert_home_cd(st);
	if (ft_strcmp("-", st->arg[1]) == 0)
	{
		if (ft_find_env_cd(lst))
		{
			free(st->arg[1]);
			st->arg[1] = ft_strdup((*lst)->path);
		}
		else
		{
			*lst = cpy;
			return ;
		}
	}
	if (!st->arg[2] && (ft_file_error_cd(st)) == 1)
	{
		ft_new_oldpwd(lst);
		chdir(st->arg[1]);
		ft_new_pwd(lst);
	}
	ft_cpy_env_st(st, lst);
}
