/* ************************************************************************** */
/*                                                          LE - /            */
/*                                                              /             */
/*   ft_convert_string.c                              .::    .:/ .      .::   */
/*                                                 +:+:+   +:    +:  +:+:+    */
/*   By: kgrosjea <kgrosjea@student.le-101.fr>      +:+   +:    +:    +:+     */
/*                                                 #+#   #+    #+    #+#      */
/*   Created: 2018/11/05 19:30:36 by kgrosjea     #+#   ##    ##    #+#       */
/*   Updated: 2018/11/30 15:34:23 by kgrosjea    ###    #+. /#+    ###.fr     */
/*                                                         /                  */
/*                                                        /                   */
/* ************************************************************************** */

#include "libft.h"

static char	*set_str(t_format *format, size_t b)
{
	char	*str;

	str = NULL;
	if (!(str = ft_strnew(format->width > b ? format->width - b : 0)))
		return (NULL);
	ft_memset((void *)str, (format->flags && format->flags->zero) ? '0' : ' ',
				format->width > b ? format->width - b : 0);
	return (str);
}

char		*format_string(t_format *format, size_t *length, char *arg)
{
	char	*str;

	str = NULL;
	if (!arg)
		str = ft_strdup(NULLSTR);
	else
		str = ft_strdup(arg);
	if (format->point && format->precision < ft_strlen(str))
		str = ft_strsub(str, 0, format->precision);
	if (format->flags && format->flags->minus)
		str = ft_strjoin_f(str, set_str(format, ft_strlen(str)));
	else
		str = ft_strjoin_f(set_str(format, ft_strlen(str)), str);
	*length = ft_strlen(str);
	return (str);
}

char		*convert_string(t_format *format, size_t *len, va_list args)
{
	return (format_string(format, len, va_arg(args, char *)));
}
