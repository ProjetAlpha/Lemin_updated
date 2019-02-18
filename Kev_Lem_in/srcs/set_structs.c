/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   set_structs.c                                    .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/20 15:12:16 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/11 14:05:13 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	set_pos(t_pos *pos, int x, int y)
{
	pos->x = x;
	pos->y = y;
}

void	set_room(t_room *room, char *name, int pos_x, int pos_y)
{
	if (name)
		room->name = ft_strdup(name);
	set_pos(&(room->pos), pos_x, pos_y);
}
