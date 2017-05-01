/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <avongdar@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:49:09 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/27 16:49:09 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		main(int ac, char const *av[])
{
	t_database *db;
	t_env env;

	env.db_in_use = load_db("db");
	env.tbl_in_use = env.db_in_use->tables;
	read_input(&env);

	free(env.db_in_use);
	return (0);
}
