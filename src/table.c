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

char		*get_table_path(char *db_path, char *table)
{
	struct stat	st;
	char		*tab_path;

	tab_path = calloc((strlen(db_path) + strlen(table) + 7), sizeof(char));
	strcat(tab_path, db_path);
	strcat(tab_path, "t_");
	strcat(tab_path, table);
	strcat(tab_path, ".csv");
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

int			create_table(char *db, t_table *table)
{
	struct stat	st;
	char		*table_path;
	char		*db_path;

	db_path = get_db_path(db);
	if (stat(db_path, &st) == -1)
	{
		printf("Error: Couldn't create table. Database does not exist.\n");
		free(db_path);
		return (0);
	}
	table_path = get_table_path(db_path, table->name);
	if (stat(table_path, &st) == -1)
		write_table(db, table);
	free(db_path);
	free(table_path);
	return (1);
}

void		display_table(t_table *table)
{
	int r;
	int c;
	t_field field;

	r = -1;
	while (++r < table->num_rows)
	{
		c = -1;
		while (++c < table->num_cols)
		{
			field = table->fields[c];
			if (field.data_type == FT_STRING)
				printf("row %s: %s\n", field.name, field.str_rows[r]);
			else if (field.data_type == FT_INT)
				printf("row %s: %d\n", field.name, field.int_rows[r]);
		}
		// printf("field %s\n", field.name);
	}
}

void		free_fields(t_field *fields, int num_fields, int num_rows)
{
	int i;
	int j;

	i = -1;
	while (++i < num_fields)
	{
		free(fields[i].name);
		if (fields[i].data_type == FT_STRING)
		{
			j = -1;
			while(++j < num_rows)
				free(fields[i].str_rows[j]);
			free(fields[i].str_rows);
		}
		if (fields[i].data_type == FT_INT)
			free(fields[i].int_rows);
	}
}

void		free_tables(t_table *tables, int num_tables)
{
	int i;

	i = -1;
	while (++i < num_tables)
	{
		free_fields(tables[i].fields, tables[i].num_cols, tables[i].num_rows);
	}
}
