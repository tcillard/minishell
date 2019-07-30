/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/07 17:55:48 by tcillard          #+#    #+#             */
/*   Updated: 2019/05/24 19:23:01 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_free_join(int s3, const char *s1, const char *s2)
{
	if (s3 == 1)
		free((char*)s1);
	else if (s3 == 2)
		free((char*)s2);
	else if (s3 == 3)
	{
		free((char*)s2);
		free((char*)s1);
	}
}

char	*ft_strjoin(const char *s1, const char *s2, int s3)
{
	int		len;
	char	*cpy;
	int		i1;
	int		i2;

	i1 = -1;
	i2 = -1;
	cpy = NULL;
	if (!s1 || !s2)
		return (NULL);
	len = ft_strlen((char*)s1) + ft_strlen((char*)s2);
	if (!(cpy = malloc(sizeof(char*) * len + 1)))
		exit(-1);
	while (s1[++i1])
		cpy[i1] = s1[i1];
	while (s2[++i2])
		cpy[i1 + i2] = s2[i2];
	cpy[i1 + i2] = '\0';
	ft_free_join(s3, s1, s2);
	return (cpy);
}
