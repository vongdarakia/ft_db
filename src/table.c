/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   table.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 22:53:58 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/27 22:53:59 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

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
