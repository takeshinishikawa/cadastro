/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_hexlen.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:14 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:10:14 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_hexlen(unsigned int number)
{
	int	count;

	count = 0;
	if (number == 0)
		count = 1;
	while (number)
	{
		number /= 16;
		count++;
	}
	return (count);
}
