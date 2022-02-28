/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unlen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:13:20 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:13:20 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_unlen(unsigned int number)
{
	int	count;

	count = 0;
	if (number == 0)
		count = 1;
	while (number)
	{
		number /= 10;
		count++;
	}
	return (count);
}
