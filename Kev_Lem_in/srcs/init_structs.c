/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   init_structs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/20 15:09:22 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/15 14:10:57 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

t_tmp	*new_tmp(void)
{
	t_tmp *tmp;

	tmp = NULL;
	if (!(tmp = (t_tmp *)malloc(sizeof(t_tmp))))
		return (NULL);
	tmp->line_format = 0;
	tmp->start = FALSE;
	tmp->end = FALSE;
	tmp->room_list = NULL;
	tmp->link_list = NULL;
	return (tmp);
}

t_room	*new_room(t_room *room)
{
	if (!(room = (t_room *)malloc(sizeof(t_room))))
		return (NULL);
	set_room(room, NULL, 0, 0);
	room->is_start = FALSE;
	room->is_end = FALSE;
	room->visited = FALSE;
	room->depth_s = 0;
	room->depth_e = 0;
	room->link_count = 0;
	room->links = NULL;
	return (room);
}

t_link	*new_link(t_link *link)
{
	if (!(link = (t_link *)malloc(sizeof(t_link))))
		return (NULL);
	link->room_1 = NULL;
	link->room_2 = NULL;
	return (link);
}

t_room	**new_room_tab(t_room **room_tab, int count)
{
	int		i;

	i = 0;
	if (count <= 0)
		return (NULL);
	if (!(room_tab = (t_room **)malloc(sizeof(t_room *) * (count + 1))))
		return (NULL);
	while (i <= count)
		room_tab[i++] = NULL;
	return (room_tab);
}

t_data	*new_data(t_data *data)
{
	if (!(data = (t_data *)malloc(sizeof(t_data))))
		return (NULL);
	data->ant_count = 0;
	data->room_count = 0;
	data->rooms = NULL;
	data->paths = NULL;
	return (data);
}
