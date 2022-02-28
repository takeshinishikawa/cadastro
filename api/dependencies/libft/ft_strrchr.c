/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:13:06 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:13:06 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	size_t			len;
	unsigned char	*aux_s;
	unsigned char	aux_c;

	len = ft_strlen(s) + 1;
	aux_s = (unsigned char *)s;
	aux_c = (unsigned char)c;
	while (len--)
	{
		if (aux_s[len] == aux_c)
			return ((char *)s + len);
	}
	return (NULL);
}
