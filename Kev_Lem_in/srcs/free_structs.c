/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   free_structs.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2019/01/29 15:15:34 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2019/01/30 15:59:43 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "lem_in.h"

void	free_tab(char **tab)
{
	int i;

	i = 0;
	if (tab)
	{
		while (tab[i])
			ft_strdel(&(tab[i++]));
		free(tab);
		tab = NULL;
	}
}
