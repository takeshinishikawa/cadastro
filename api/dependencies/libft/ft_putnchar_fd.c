/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnchar_fd.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rtakeshi <rtakeshi@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/02/16 15:12:27 by rtakeshi          #+#    #+#             */
/*   Updated: 2022/02/16 15:12:27 by rtakeshi         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	ft_putnchar_fd(char c, int n, int fd)
{
	int	counter;

	counter = 0;
	while (counter < n)
	{
		write(fd, &c, 1);
		counter++;
	}
}
