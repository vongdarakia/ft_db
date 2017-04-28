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

/*
**	get_table_path
**
**	Gets the file path of the table of the database. A table file is
**	csv file.
**
**	@param db:		Database name
**	@param table:	Table name
**	@return			File path to the table (ie. Database/Sibyl/users.csv)
*/

char	*get_table_path(char *db, char *table)
{
	struct stat	st;
	char		*db_path;
	char		*tab_path;

	db_path = get_db_path(db);
	if (stat(db_path, &st) == -1)
	{
		printf("Error: Can't get table path. Database does not exist.\n");
		return (NULL);
	}
	tab_path = calloc((strlen(db_path) + strlen(table) + 5), sizeof(char));
	strcat(tab_path, db_path);
	strcat(tab_path, table);
	strcat(tab_path, ".csv");
	free(db_path);
	return (tab_path);
}

/*
**	create_table
**
**	Creates a table csv file for the given database.
**
**	@param db:		Database name
**	@param table:	Table name
*/

void	create_table(char *db, char *table)
{
	struct stat	st;
	char		*table_path;

	table_path = get_table_path(db, table);
	if (table_path == NULL)
	{
		printf("Error: Can't create table. Invalid table path.\n");
		return ;
	}
	free(table_path);
}

int		main(int ac, char const *av[])
{
	create_db("db");
	create_table("db", "table");
	return (0);
}
