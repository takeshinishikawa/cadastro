/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:13:03 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:13:04 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strnstr(const char *haystack, const char *needle, size_t len)
{
	size_t	h;
	size_t	n;
	size_t	aux;

	h = 0;
	n = ft_strlen(needle);
	if (n == 0)
		return ((char *)haystack);
	while (haystack[h] && h < len)
	{
		aux = 0;
		while ((haystack[h + aux] == needle[aux]) && ((h + aux) < len))
		{
			if (aux + 1 == n)
				return ((char *)haystack + h);
			aux++;
		}
		h++;
	}
	return (0);
}
