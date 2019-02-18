/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   check_format.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/27 10:57:57 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 13:21:28 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static int	check_room(const char *line)
{
	char **parts;

	parts = NULL;
	if (ft_strctn(line, '-'))
		return (INVALID);
	if (!(parts = ft_strsplit(line, ' ')))
		return (INVALID);
	if (ft_tablen(parts) != 3)
		return (INVALID);
	if (!ft_isnumber(parts[1]) || !ft_isnumber(parts[2]))
		return (INVALID);
	return (ROOM);
}

static int	check_link(const char *line)
{
	char **parts;

	parts = NULL;
	if (!(parts = ft_strsplit(line, '-')))
		return (INVALID);
	if (ft_tablen(parts) != 2)
		return (INVALID);
	if (!ft_strcmp(parts[0], parts[1]))
		return (INVALID);
	if (parts[1][0] == '#' || parts[1][0] == 'L')
		return (INVALID);
	return (LINK);
}

int			check_line(const char *line)
{
	if (line && ft_strlen(line) > 0 && line[0] != 'L')
	{
		if (line[0] == '#')
		{
			if (ft_strlen(line) > 1 && line[1] == '#')
				return (COMMAND);
			else
				return (COMMENT);
		}
		else
		{
			if (ft_strctn(line, ' '))
				return (check_room(line));
			else if (ft_strctn(line, '-'))
				return (check_link(line));
			else
				return (INVALID);
		}
	}
	else
		return (INVALID);
	return (0);
}
