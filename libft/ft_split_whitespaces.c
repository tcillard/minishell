/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split_whitespaces.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/15 15:47:13 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/18 09:26:38 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int		ft_count_cara(char *str)
{
	int a;

	a = 0;
	while (str[a] != '\n' && str[a] != '\t' && str[a] != ' ' && str[a] != '\0')
		a++;
	return (a + 1);
}

int		ft_count_world(char *str)
{
	int		j;
	int		a;

	j = 0;
	a = 0;
	if (str[j] != '\n' && str[j] != '\t' && str[j] != ' ')
		a++;
	j++;
	while (str[j])
	{
		if ((str[j - 1] == '\n' || str[j - 1] == '\t' || str[j - 1] == ' ')
				&& (str[j] != '\n' && str[j] != '\t' && str[j] != ' '))
			a++;
		j++;
	}
	return (a);
}

char	**ft_split_whitespaces(char *str)
{
	int		y;
	int		i;
	int		nb;
	char	**tab;

	if (!(nb = ft_count_world(str)))
		return (NULL);
	i = 0;
	tab = malloc(sizeof(char*) * nb + 1);
	while (i < nb)
	{
		y = 0;
		while (*str == '\n' || *str == '\t' || *str == ' ')
			str++;
		if (!(tab[i] = malloc(sizeof(char) * ft_count_cara(str) + 1)))
			return (0);
		while (*str != '\n' && *str != '\t' && *str != ' ' && *str != '\0')
		{
			tab[i][y] = *str;
			str++ && y++;
		}
		tab[i][y] = '\0';
		i++;
	}
	return (tab);
}
