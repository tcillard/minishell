/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/16 01:51:24 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/25 10:53:46 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_bin(t_minishell *st)
{
	ft_putstr_fd("minishell: command not found: ", 2);
	ft_putstr_fd(st->arg[0], 2);
	ft_putchar_fd('\n', 2);
	exit(-1);
}

void	ft_error_access(char *error)
{
	ft_putstr_fd("cd", 2);
	ft_putstr_fd(": permission denied: ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

void	ft_error_file(char *error)
{
	ft_putstr_fd("cd", 2);
	ft_putstr_fd(": not a directory: ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}

void	ft_error_exist(char *error)
{
	ft_putstr_fd("cd", 2);
	ft_putstr_fd(": no such file or directory: ", 2);
	ft_putstr_fd(error, 2);
	write(2, "\n", 1);
}
