/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_next_line.c                                  .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/10/08 16:25:40 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 15:05:37 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"
#include <stdio.h>

static char			*ft_readl(const int fd, char *dst)
{
	int		ret;
	char	buffer[BUFF_SIZE + 1];

	ret = 1;
	if (!dst)
		dst = ft_strnew(0);
	while (!(ft_strctn(dst, '\n')) && ret > 0)
	{
		if ((ret = read(fd, buffer, BUFF_SIZE)) == -1)
			return (NULL);
		buffer[ret] = '\0';
		dst = ft_strjoin_f(dst, ft_strdup(buffer));
	}
	return (dst);
}

static t_restfd		*ft_get_struct(const int fd, t_restfd **first)
{
	t_restfd	*tmp;
	t_restfd	*curr;

	curr = *first;
	tmp = NULL;
	if (*first)
	{
		if (curr->fd == fd)
			return (curr);
		while (curr->next)
			if (curr->next->fd == fd)
				return (curr->next);
			else
				curr = curr->next;
	}
	if (!(tmp = (t_restfd *)malloc(sizeof(t_restfd))))
		return (NULL);
	tmp->fd = fd;
	tmp->rest = NULL;
	tmp->next = NULL;
	if (curr)
		curr->next = tmp;
	else
		*first = tmp;
	return (tmp);
}

static int			ft_clean(t_restfd **first, t_restfd *curr, int ret)
{
	t_restfd	*tmp;

	tmp = NULL;
	if (curr == *first)
		*first = curr->next;
	else
	{
		tmp = *first;
		while (tmp->next != curr)
			tmp = tmp->next;
		tmp->next = curr->next;
	}
	curr->fd = 0;
	ft_strdel(&curr->rest);
	curr->next = NULL;
	free(curr);
	return (ret);
}

int					get_next_line(const int fd, char **line)
{
	static t_restfd	*first = NULL;
	t_restfd		*curr;
	char			*tmp;
	int				line_len;

	curr = ft_get_struct(fd, &first);
	if (!line || fd < 0 || BUFF_SIZE <= 0 || read(fd, NULL, 0) < 0 ||
		!(curr->rest = ft_readl(curr->fd, curr->rest)))
		return (ft_clean(&first, curr, -1));
	if (!*curr->rest)
		return (ft_clean(&first, curr, 0));
	line_len = 0;
	while (curr->rest[line_len] != '\n' && curr->rest[line_len])
		line_len++;
	if (!curr->rest[line_len])
		curr->rest = ft_strjoin_f(curr->rest, ft_strdup("\n"));
	*line = ft_strncpy(ft_strnew(line_len), curr->rest, line_len);
	tmp = curr->rest;
	curr->rest = ft_strdup(tmp + line_len + 1);
	ft_strdel(&tmp);
	return (1);
}
