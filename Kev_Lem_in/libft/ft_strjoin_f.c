/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_strjoin_f.c                                   .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/13 15:17:50 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/12/09 19:59:22 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin_f(char *s1, char *s2)
{
	char *str;

	str = NULL;
	str = ft_strjoin(s1, s2);
	free(s1);
	free(s2);
	return (str);
}
