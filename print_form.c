/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_form.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: smaccary <smaccary@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/01/31 04:00:46 by smaccary          #+#    #+#             */
/*   Updated: 2020/02/15 14:32:07 by smaccary         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libftprintf.h"
#include <stdio.h>

int	handler(t_infos infos, va_list *list)
{
	int ret;

	if (ft_strchr("pudixX", infos.conv) && !infos.width && infos.dot
		&& !get_curr_int(list))
	{
		(void)va_arg(*list, int);
		ret = (infos.conv == 'p') ? infos.printer(1, "0x", 2) : 0;
		return (ret + print_space_str('0', infos.precision, infos.printer));
	}
	if (infos.width || infos.precision)
		return (print_space(&infos, list));
	else
		return (print_conv(infos, list));
	return (0);
}

int	print_form(const char *format, va_list *list,
	ssize_t (*my_write)(int, const void *, size_t))
{
	char	*str;
	t_infos infos;

	if (!(str = ft_substr(format, 0,
		get_conv((char *)format) + 1 - format)))
		return (my_write(1, "ERROR", 5));
	infos = get_infos(str, list, (*my_write));
	free(str);
	return (handler(infos, list));
}
