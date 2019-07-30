/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: tcillard <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/07 15:24:46 by tcillard          #+#    #+#             */
/*   Updated: 2019/04/27 16:33:38 by tcillard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "get_next_line.h"

t_gnl	*ft_lstgnlnew(int fd)
{
	t_gnl *lst;

	if (!(lst = malloc(sizeof(t_gnl))))
		return (NULL);
	lst->fd = fd;
	if (!(lst->str = ft_strnew(0)))
		return (NULL);
	lst->next = NULL;
	return (lst);
}

t_gnl	*ft_search_fd(int fd, t_gnl *search)
{
	t_gnl	*maillon;

	if (!search)
	{
		if (!(maillon = ft_lstgnlnew(fd)))
			return (0);
		return (maillon);
	}
	while (search->fd != fd && search->next != NULL)
		search = search->next;
	if (search->fd == fd)
		return (search);
	if (!(maillon = ft_lstgnlnew(fd)))
		return (0);
	search->next = maillon;
	return (maillon);
}

int		ft_write_to_line(char **line, char **str, int *r)
{
	size_t	i;
	char	*tmp;

	tmp = NULL;
	i = 0;
	if ((*str)[0] == '\n')
	{
		if (!(*line = ft_strdup(""))
				|| !(tmp = ft_strsub(*str, 1, ft_strlen(*str) - 1)))
			return (-1);
		free(*str);
		*str = tmp;
		*r = 1;
		return (1);
	}
	while ((*str)[i] != '\n' && (*str)[i] != '\0')
		i++;
	if (!(*line = ft_strsub(*str, 0, i)))
		return (-1);
	if (((*str)[i] && !(tmp = ft_strsub(*str, i + 1, ft_strlen(*str) - i)))
			|| (!tmp && !(tmp = ft_strdup(""))))
		return (-1);
	free(*str);
	*str = tmp;
	return (1);
}

int		ft_lstfree(int fd, t_gnl **lst)
{
	t_gnl *cpy;

	cpy = *lst;
	while ((*lst)->fd != fd && *lst)
	{
		cpy = *lst;
		*lst = (*lst)->next;
	}
	if (*lst && (*lst)->fd == fd)
	{
		free((*lst)->str);
		(*lst)->str = NULL;
		cpy->next = (*lst)->next;
		(*lst)->next = NULL;
		free(*lst);
		*lst = NULL;
	}
	return (1);
}

int		get_next_line(const int fd, char **line)
{
	static t_gnl	*first;
	t_gnl			*cpy;
	char			*cpy_free;
	char			buff[BUFF_SIZE + 1];
	int				ret;

	ret = 0;
	if (fd < 0 || !line || ((!first) && ((!(first = ft_lstgnlnew(fd)))))
			|| !(cpy = ft_search_fd(fd, first)))
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		cpy_free = cpy->str;
		if (!(cpy->str = ft_strjoin(cpy->str, (const char*)buff)))
			return (-1);
		free(cpy_free);
		if (ft_strchr((const char*)buff, '\n'))
			break ;
	}
	if (!ft_write_to_line(line, &cpy->str, &ret) || ret < 0)
		return (-1);
	if (ret == 0 && (!(**line) && !(*(cpy->str))) && ft_lstfree(fd, &first))
		return (0);
	return (1);
}
