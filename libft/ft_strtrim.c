/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/09/23 02:58:01 by ynenakho          #+#    #+#             */
/*   Updated: 2017/11/28 16:17:08 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s)
{
	char		*new;
	int			str_len;

	if (!s)
		return (NULL);
	while (STRTRIM_CONDITION && *s != '\0')
		s++;
	str_len = (!*s) ? (0) : (ft_strlen(s) - 1);
	while (s[str_len] == ' ' || s[str_len] == '\n' || s[str_len] == '\t')
		str_len--;
	str_len = &s[str_len] - s;
	new = ((!str_len) ? ft_strnew(0) : (ft_strsub(s, 0, str_len + 1)));
	if (!new)
		return (NULL);
	return (new);
}
