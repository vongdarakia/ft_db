/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_word_count.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/10/21 00:56:08 by avongdar          #+#    #+#             */
/*   Updated: 2016/10/21 00:59:00 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_word_count(char *s)
{
	int i;
	int wc;

	i = -1;
	wc = 0;
	while (s[++i])
		if (!ft_isspace(s[i]) && (ft_isspace(s[i + 1]) || s[i + 1] == 0))
			wc++;
	return (wc);
}
