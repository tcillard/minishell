/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_lst_env.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/22 07:00:13 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/29 16:10:08 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_env	*ft_lst_init(t_env *past)
{
	t_env	*lst;

	if (!(lst = malloc(sizeof(t_env))))
		exit(-1);
	lst->name = NULL;
	lst->path = NULL;
	lst->next = NULL;
	lst->prev = past;
	return (lst);
}

void	ft_record_lst_env(t_env **lst, char *env)
{
	int		j;
	int		j_pa;

	j = 0;
	j_pa = 0;
	while (env[j] != '=')
		j++;
	if (!((*lst)->name = malloc(sizeof(char) * j + 1)))
		exit(-1);
	if (!((*lst)->path = malloc((ft_strlen(env) - j))))
		exit(-1);
	j = -1;
	while (env[++j] != '=')
		(*lst)->name[j] = env[j];
	(*lst)->name[j++] = '\0';
	if (ft_strcmp((*lst)->name, "SHLVL") == 0)
		ft_shlvl(lst, env);
	else
	{
		while (env[j])
			(*lst)->path[j_pa++] = env[j++];
		(*lst)->path[j_pa] = '\0';
	}
}

void	ft_write_st(t_minishell *st, t_env **lst, int i)
{
	int		j;
	int		j2;
	int		len;

	j = -1;
	j2 = 0;
	len = ft_strlen((*lst)->name) + ft_strlen((*lst)->path);
	if (!(st->env[i] = malloc(sizeof(char) * (len + 2))))
		exit(-1);
	while ((*lst)->name[++j])
		st->env[i][j] = (*lst)->name[j];
	st->env[i][j++] = '=';
	while ((*lst)->path[j2])
		st->env[i][j++] = (*lst)->path[j2++];
	st->env[i][j] = '\0';
}

void	ft_cpy_env_st(t_minishell *st, t_env **lst)
{
	int		i;
	t_env	*cpy;

	i = 0;
	cpy = *lst;
	while (*lst)
	{
		*lst = (*lst)->next;
		i++;
	}
	*lst = cpy;
	if (st->env)
		ft_free_env(st);
	if (!(st->env = malloc(sizeof(char*) * (i + 1))))
		exit(-1);
	i = 0;
	while (*lst)
	{
		ft_write_st(st, lst, i++);
		*lst = (*lst)->next;
	}
	st->env[i] = NULL;
	*lst = cpy;
}

void	ft_creat_lst_env(t_env **lst, t_minishell *st, char **env)
{
	int		i;
	t_env	*cpy;

	cpy = NULL;
	i = 0;
	if (env[i])
	{
		*lst = ft_lst_init(NULL);
		cpy = *lst;
		while (env[i])
		{
			(*lst)->next = ft_lst_init(*lst);
			ft_record_lst_env(lst, env[i]);
			*lst = (*lst)->next;
			i++;
		}
		if ((*lst)->prev)
			(*lst)->prev->next = NULL;
		free(*lst);
		*lst = cpy;
		ft_cpy_env_st(st, lst);
	}
	else
		ft_env_base(lst, st);
}
