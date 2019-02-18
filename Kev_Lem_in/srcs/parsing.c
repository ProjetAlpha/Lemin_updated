/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   parsing.c                                        .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/21 13:06:32 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 15:05:31 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

static t_tmp	*add_room_to_tmp(const char *line, t_tmp *tmp)
{
	t_room	*room;

	room = NULL;
	if (!(room = get_room(line, tmp)))
		return (NULL);
	if (!(tmp->room_list = add_elem_to_list((void *)room, tmp->room_list)))
		return (NULL);
	return (tmp);
}

static t_tmp	*add_link_to_tmp(const char *line, t_tmp *tmp)
{
	t_link	*link;

	link = NULL;
	if (!(link = get_link(line, tmp)))
		return (NULL);
	if (!(tmp->link_list = add_elem_to_list((void *)link, tmp->link_list)))
		return (NULL);
	return (tmp);
}

t_data			*parse_data(t_data *data)
{
	char	*line;
	t_tmp	*tmp;

	line = NULL;
	tmp = NULL;
	if (!(tmp = new_tmp()))
		return (NULL);
	data->ant_count = get_ant_count(data);
	while (get_next_line(0, &line) > 0)
	{
		tmp->line_format = check_line(line);
		if (tmp->line_format == COMMAND)
		{
			if (!ft_strcmp(line, "##start"))
				tmp->start = TRUE;
			else if (!ft_strcmp(line, "##end"))
				tmp->end = TRUE;
		}
		else if (tmp->line_format == ROOM)
		{
			if (!(tmp = add_room_to_tmp(line, tmp)))
				return (fill_data(tmp, data));
		}
		else if (tmp->line_format == LINK)
		{
			if (!(tmp = add_link_to_tmp(line, tmp)))
				return (fill_data(tmp, data));
		}
		else if (tmp->line_format == INVALID)
			return (fill_data(tmp, data));
		ft_strdel(&line);
	}
	return (fill_data(tmp, data));
}
