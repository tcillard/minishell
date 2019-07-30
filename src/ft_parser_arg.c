/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parser_arg.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/17 04:05:59 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/26 02:07:38 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_quote(char c, t_minishell *st)
{
	if (!((*st).quote & QUOTE) && c == '\'' && (!((*st).quote & APOS)))
		(*st).quote += APOS;
	else if (c == '\'' && (*st).quote & APOS)
		(*st).quote -= APOS;
	else if (!((*st).quote & APOS) && c == '\"' && !((*st).quote & QUOTE))
		(*st).quote += QUOTE;
	else if (c == '\"' && (*st).quote & QUOTE)
		(*st).quote -= QUOTE;
}

int		ft_count_arg(t_minishell *st)
{
	int		i;
	int		count;
	int		cpy;

	cpy = 0;
	i = 0;
	count = 0;
	while ((*st).tmp[i] && (*st).tmp[i] != '\n')
	{
		while (((*st).tmp[i] == ' ' || (*st).tmp[i] == '\t'))
			i++;
		if (st->tmp[i] == '\n')
			return (count);
		ft_quote((*st).tmp[i], st);
		cpy = (*st).quote;
		if ((*st).quote)
			i++;
		while ((*st).quote || (st->tmp[i] != '\n' && (*st).tmp[i] != '\t'
					&& (*st).tmp[i] != ' '))
			ft_quote((*st).tmp[i++], st);
		++count;
	}
	return (count);
}

void	ft_count_car(int *index, int *i, t_minishell *st)
{
	int		cpy;
	int		count;

	cpy = 0;
	count = 0;
	while ((*st).tmp[*i] == ' ' || (*st).tmp[*i] == '\t')
		(*i)++;
	ft_quote((*st).tmp[*i], st);
	if ((*st).quote)
		(*i)++;
	cpy = (*st).quote;
	while ((*st).quote || (st->tmp[*i] != '\n' && (*st).tmp[*i] != '\t'
				&& (*st).tmp[*i] != ' ' && st->tmp[*i]))
	{
		ft_quote((*st).tmp[*i], st);
		if (cpy != (*st).quote)
			count--;
		cpy = st->quote;
		count++;
		(*i)++;
	}
	if (!((*st).arg[(*index)++] = malloc(sizeof(char) * (count + 1))))
		exit(-1);
}

void	ft_write_arg(int *index, int *i, t_minishell *st)
{
	int		cpy;
	int		j;

	j = 0;
	cpy = 0;
	while ((*st).tmp[*i] == ' ' || (*st).tmp[*i] == '\t')
		(*i)++;
	if (st->tmp[*i] == '\n')
		return ;
	ft_quote((*st).tmp[*i], st);
	if ((*st).quote)
		(*i)++;
	cpy = (*st).quote;
	while ((*st).quote || (st->tmp[*i] != '\t' && (*st).tmp[*i] != '\n'
				&& (*st).tmp[*i] != ' ' && st->tmp[*i]))
	{
		ft_quote((*st).tmp[*i], st);
		if (cpy == (*st).quote)
			(*st).arg[*index][j++] = (*st).tmp[*i];
		cpy = st->quote;
		(*i)++;
	}
	(*st).arg[*index][j] = '\0';
	(*index)++;
}

void	ft_split_shell(t_minishell *st)
{
	int		len;
	int		i;
	int		index;

	index = 0;
	i = 0;
	len = ft_count_arg(st);
	if (!len)
		return ;
	if (!((*st).arg = malloc(sizeof(char*) * (len + 1))))
		exit(-1);
	while ((*st).tmp[i] && (*st).tmp[i] != '\n')
		ft_count_car(&index, &i, st);
	i = 0;
	index = 0;
	while ((*st).tmp[i] && (*st).tmp[i] != '\n')
		ft_write_arg(&index, &i, st);
	(*st).arg[index] = NULL;
}
