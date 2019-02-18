/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   get_data.c                                       .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 15:05:51 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/13 15:05:27 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

int			get_ant_count(t_data *data)
{
	char *line;

	line = NULL;
	while (get_next_line(0, &line) > 0)
	{
		if (ft_strlen(line) > 0 && line[0] != '#')
		{
			if (ft_isnumber(line) && ft_atoi(line) > 0)
				return (ft_atoi(line));
			else
				return (clean_exit(data, "Invalid ant count !"));
		}
		ft_strdel(&line);
	}
	return (clean_exit(data, "No ant count found !"));
}

t_room	*get_room(const char *line, t_tmp *tmp)
{
	char		**parts;
	t_room		*room;

	parts = NULL;
	room = NULL;
	if (!(parts = ft_strsplit(line, ' ')))
		return (NULL);
	if (!(room = new_room(room)))
		return (NULL);
	set_room(room, parts[0], ft_atoi(parts[1]), ft_atoi(parts[2]));
	room->is_start = tmp->start;
	tmp->start = FALSE;
	room->is_end = tmp->end;
	tmp->end = FALSE;
	free_tab(parts);
	return (room);
}

t_link	*get_link(const char *line, t_tmp *tmp)
{
	char	**parts;
	t_link	*link;
	t_tmp_list	*curr;
	t_room	*tmp_room;

	parts = NULL;
	link = NULL;
	curr = tmp->room_list;
	if (!(parts = ft_strsplit(line, '-')))
		return (NULL);
	if (!(link = new_link(link)))
		return (NULL);
	while (curr && (!link->room_1 || !link->room_2))
	{
		tmp_room = (t_room *)curr->elem;
		if (!ft_strcmp(tmp_room->name, parts[0]))
			link->room_1 = (t_room *)curr->elem;
		if (!ft_strcmp(tmp_room->name, parts[1]))
			link->room_2 = (t_room *)curr->elem;
		curr = curr->next;
	}
	free_tab(parts);
	if (!link->room_1 || !link->room_2)
	{
		printf("missing a room for link\n");
		return (NULL);
	}
	return (link);
}
