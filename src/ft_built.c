/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_find_built.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 17:33:55 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/25 09:10:56 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void		ft_find_built(t_minishell *st, t_env **lst)
{
	if (st->builtins & ECHO)
		ft_echo(st);
	if (st->builtins & CD)
		ft_cd(st, lst);
	if ((st->builtins & ENV) && *lst)
		ft_putenv(st);
	if (st->builtins & SETENV)
		ft_set_env(st, lst);
	if ((st->builtins & UNSETENV) && *lst)
		ft_unset_env(st, lst);
}
