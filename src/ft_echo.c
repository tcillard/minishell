/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 02:12:24 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/26 02:06:29 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(t_minishell *st)
{
	int		i;
	int		opt;

	opt = 0;
	i = 1;
	if (!(st->arg[1]))
	{
		ft_putchar('\n');
		return ;
	}
	if (ft_strcmp(st->arg[1], "-n") == 0)
	{
		opt++;
		i++;
	}
	while (st->arg[i])
	{
		ft_putstr(st->arg[i++]);
		if (st->arg[i] && st->arg[i + 1])
			ft_putchar(' ');
	}
	if (opt == 0)
		ft_putchar('\n');
}
