/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_fill_format.c                                 .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/01 16:10:37 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:34:33 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

t_bool	set_flags(t_format *format, char *flags)
{
	t_flags *format_flags;

	if (!(format_flags = create_new_t_flags()))
		return (FALSE);
	if (ft_strctn(flags, '#'))
		format_flags->hashtag = TRUE;
	if (ft_strctn(flags, '-'))
		format_flags->minus = TRUE;
	else if (ft_strctn(flags, '0'))
		format_flags->zero = TRUE;
	if (ft_strctn(flags, '+'))
		format_flags->plus = TRUE;
	else if (ft_strctn(flags, ' '))
		format_flags->space = TRUE;
	if (ft_strctn(flags, '\''))
		format_flags->coma = TRUE;
	format->flags = format_flags;
	free(flags);
	return (TRUE);
}

int		set_width(t_format *format, char *width)
{
	size_t len;

	len = 0;
	if (!width)
		return (0);
	format->width = (size_t)ft_atoi(width);
	len = ft_strlen(width);
	free(width);
	return (len);
}

int		set_point(t_format *format, const char *sub_expr)
{
	if (*sub_expr == '.')
	{
		format->point = TRUE;
		return (1);
	}
	return (0);
}

int		set_precision(t_format *format, char *precision)
{
	size_t len;

	len = 0;
	if (!precision)
		return (0);
	format->precision = (size_t)ft_atoi(precision);
	len = ft_strlen(precision);
	free(precision);
	return (len);
}

int		set_length(t_format *format, char *length)
{
	size_t len;

	len = 0;
	if (!length)
		return (0);
	format->length = ft_strdup(length);
	len = ft_strlen(length);
	free(length);
	return (len);
}
