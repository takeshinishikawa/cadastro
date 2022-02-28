/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:10:39 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:10:49 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_itoa(int n)
{
	char	*cvt_int;
	int		signal;
	size_t	len;

	signal = 1;
	len = ft_nlen(n);
	cvt_int = (char *)malloc((len + 1) * sizeof(char));
	if (cvt_int == NULL)
		return (NULL);
	cvt_int[len] = '\0';
	len--;
	if (n < 0)
		signal *= -1;
	while (n != 0)
	{
		cvt_int[len] = (n % 10 * signal) + '0';
		n /= 10;
		len--;
	}
	if (len == 0 && cvt_int[1] == '\0')
		cvt_int[len] = '0';
	else if (len == 0 && cvt_int[1] != '\0')
		cvt_int[len] = '-';
	return (cvt_int);
}
