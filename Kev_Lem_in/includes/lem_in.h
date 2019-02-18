/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   lem_in.h                                         .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/20 14:49:34 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/02/16 18:18:45 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "libft.h"
# include <stdio.h>
# define ROOM 1
# define LINK 2
# define COMMAND 3
# define COMMENT 4
# define INVALID 5

typedef struct	s_pos
{
	int	x;
	int	y;
}				t_pos;

typedef struct	s_tmp_list
{
	void			*elem;
	int 			len;
	struct s_tmp_list	*next;
}				t_tmp_list;

typedef struct	s_room
{
	char			*name;
	t_pos			pos;
	t_bool		is_start;
	t_bool		is_end;
	t_bool		visited;
	int				depth_s;
	int				depth_e;
	int				link_count;
	struct s_room	**links;
}				t_room;

typedef struct	s_link
{
	t_room	*room_1;
	t_room	*room_2;
}				t_link;

typedef struct	s_tmp
{
	int		line_format;
	t_bool	start;
	t_bool	end;
	t_tmp_list	*room_list;
	t_tmp_list	*link_list;
}				t_tmp;

typedef struct	s_data
{
	int			ant_count;
	int			room_count;
	t_room		**rooms;
	t_tmp_list	*paths;
}				t_data;

t_data		*new_data(t_data *data);
t_tmp		*new_tmp(void);
t_room		*new_room(t_room *room);
t_link		*new_link(t_link *link);
t_room		**new_room_tab(t_room **room_tab, int count);
t_tmp_list	*new_tmp_list(void *elem);
void		set_pos(t_pos *pos, int x, int y);
void		set_room(t_room *room, char *name, int pos_x, int pos_y);
t_data		*parse_data(t_data *data);
int			check_line(const char *line);
int			get_ant_count(t_data *data);
t_room		*get_room(const char *line, t_tmp *tmp);
t_link		*get_link(const char *line, t_tmp *tmp);
t_tmp_list	*add_elem_to_list(void *elem, t_tmp_list *list);
t_data		*fill_data(t_tmp *tmp, t_data *data);
t_data		*update_data(t_data *data);
t_data		*clean_data(t_data *data);
t_data		*optimize_data(t_data *data);
t_bool		check_data(t_data *data);
int			backtrack(t_data *data);
t_bool		ft_isnumber(char *line);
int			ft_tablen(char **tab);
t_room		*check_room_name(char *name, t_tmp_list *list);
int			clean_exit(t_data *data, const char *msg);
void		free_tab(char **tab);

#endif
