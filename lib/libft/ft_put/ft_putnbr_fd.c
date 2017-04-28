/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 10:11:02 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 12:06:21 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr_fd(int n, int fd)
{
	const char base[] = "0123456789";

	if (n == 0)
	{
		write(fd, "0", 1);
		return ;
	}
	if (n < 0 && n > -10)
		write(fd, "-", 1);
	if (n <= -10 || n >= 10)
		ft_putnbr_fd(n / 10, fd);
	write(fd, base + (n % 10) * (n < 0 ? -1 : 1), 1);
}
