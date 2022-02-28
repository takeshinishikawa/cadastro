/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memccpy.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:11:30 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:11:30 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_memccpy(void *dst, const void *src, int c, size_t n)
{
	size_t	counter;

	counter = 0;
	if (!dst && !src)
		return (0);
	while (counter < n)
	{
		((unsigned char *)dst)[counter] = ((unsigned char *)src)[counter];
		if (((unsigned char *)src)[counter] == (unsigned char)c)
			return (dst + counter + 1);
		counter++;
	}
	return (0);
}
