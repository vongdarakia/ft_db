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

void	create_db(char *db)
{
	struct stat	st;
	char		*new_db;

	if (stat(DB_DIR, &st) == -1)
	{
		mkdir(DB_DIR, 0755);
	}
	new_db = calloc((strlen(DB_DIR) + strlen(db) + 2), sizeof(char));
	strcat(new_db, DB_DIR);
	strcat(new_db, "/");
	strcat(new_db, db);
	if (stat(new_db, &st) == -1)
	{
		mkdir(new_db, 0755);
	}
	free(new_db);
}

int		main(int ac, char const *av[])
{
	create_db("test");
	return (0);
}
