/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   database.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 22:53:47 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/27 22:53:53 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*
**	get_db_path
**
**	Gets the database path. A database is a folder of tables (csv files).
**	The database will always be created in the Database folder of where the
**	program is running.
**
**	@param db:		Database name
**	@return			Directory path to the database (ie. Database/Sibyl/)
*/

char	*get_db_path(char *db)
{
	char	*db_path;

	db_path = calloc((strlen(DB_DIR) + strlen(db) + 3), sizeof(char));
	strcat(db_path, DB_DIR);
	strcat(db_path, "/");
	strcat(db_path, db);
	strcat(db_path, "/");
	return (db_path);
}

/*
**	create_db
**
**	Creates a database folder in the current directory.
**
**	@param db:		Database name
*/

void	create_db(char *db)
{
	struct stat	st;
	char		*new_db;

	if (stat(DB_DIR, &st) == -1)
	{
		mkdir(DB_DIR, 0755);
	}
	new_db = get_db_path(db);
	if (stat(new_db, &st) == -1)
	{
		mkdir(new_db, 0755);
	}
	free(new_db);
}
