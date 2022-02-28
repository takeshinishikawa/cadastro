/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_nlen.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:11:59 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:11:59 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_nlen(long long number)
{
	int					len;
	unsigned long long	aux;

	len = 0;
	aux = number;
	if (number == 0)
		len = 1;
	if (number < 0)
		aux = number * -1;
	while (aux)
	{
		aux /= 10;
		len++;
	}
	return (len);
}
