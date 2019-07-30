/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/20 09:56:27 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/29 16:25:36 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_replace_env(t_minishell *st, int i, int n)
{
	int		j;
	int		j2;
	int		len;
	char	*new;

	len = ft_strlen(st->arg[i]) - n;
	new = NULL;
	j = -1;
	if (!(new = malloc(sizeof(char) * len + 1)))
		exit(-1);
	while (st->arg[i][++j] != '$')
		new[j] = st->arg[i][j];
	j2 = j;
	while (st->arg[i][j] && st->arg[i][j] != ' ' && st->arg[i][j] != '\t')
		j++;
	while (st->arg[i][j])
		new[j2++] = st->arg[i][j++];
	new[j2] = '\0';
	return (new);
}

char	*ft_env_sub(t_minishell *st, int i, int n, char *path)
{
	int		j;
	int		j2;
	int		j_pa;
	char	*new;
	int		len;

	len = ft_strlen(path) + ft_strlen(st->arg[i]) - n;
	j_pa = 0;
	new = NULL;
	j = -1;
	if (!(new = malloc(sizeof(char) * len + 1)))
		exit(-1);
	while (st->arg[i][++j] != '$')
		new[j] = st->arg[i][j];
	j2 = j;
	j = j + n;
	while (path[j_pa])
		new[j2++] = path[j_pa++];
	while (st->arg[i][j])
		new[j2++] = st->arg[i][j++];
	new[j2] = '\0';
	return (new);
}

void	ft_find_env(t_minishell *st, t_env **lst, int i, int j)
{
	int		n;
	char	*cpy;
	char	*cpy_arg;

	cpy_arg = st->arg[i];
	n = 0;
	while (st->arg[i][j] && st->arg[i][j] != '\t' && st->arg[i][j] != ' ')
		++j && ++n;
	if (!(cpy = malloc(sizeof(char) * n + 1)))
		exit(-1);
	j = j - n;
	n = 0;
	while (st->arg[i][j] && st->arg[i][j] != '\t' && st->arg[i][j] != ' ')
		cpy[n++] = st->arg[i][j++];
	cpy[n] = '\0';
	while ((*lst)->next && ft_strcmp(cpy, (*lst)->name) != 0)
		(*lst) = (*lst)->next;
	if ((ft_strcmp((*lst)->name, cpy) != 0))
		st->arg[i] = ft_replace_env(st, i, ++n);
	else
		st->arg[i] = ft_env_sub(st, i, ++n, (*lst)->path);
	free(cpy_arg);
	free(cpy);
	while ((*lst)->prev)
		*lst = (*lst)->prev;
}

void	ft_env(t_minishell *st, t_env **lst)
{
	int		i;
	int		j;

	i = 0;
	while (st->arg[i])
	{
		j = 0;
		while (st->arg[i][j])
		{
			if (st->arg[i][j] == '$' && (*lst))
			{
				ft_find_env(st, lst, i, ++j);
				break ;
			}
			else if (st->arg[i][0] == '~' && !(st->arg[i][1]))
			{
				ft_replace_home(st, lst, i);
				break ;
			}
			j++;
		}
		i++;
	}
}

void	ft_putenv(t_minishell *st)
{
	int		i;

	i = 0;
	while (st->env[i])
	{
		ft_putstr(st->env[i++]);
		ft_putchar('\n');
	}
}
