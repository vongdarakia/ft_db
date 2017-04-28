/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/09/23 10:10:15 by avongdar          #+#    #+#             */
/*   Updated: 2016/09/23 10:10:17 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>

void	ft_putnbr(int n)
{
	const char base[] = "0123456789";

	if (n == 0)
	{
		write(1, "0", 1);
		return ;
	}
	if (n < 0 && n > -10)
		write(1, "-", 1);
	if (n <= -10 || n >= 10)
		ft_putnbr(n / 10);
	write(1, base + (n % 10) * (n < 0 ? -1 : 1), 1);
}
