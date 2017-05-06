/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_mngr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/05/05 19:38:30 by avongdar          #+#    #+#             */
/*   Updated: 2017/05/05 19:38:32 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void	call_error(int err_code)
{
	printf("Error. Code: %d\n", err_code);
	printf("Type \"help\" to see proper usage\n");
}
