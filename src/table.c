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

	tab_path = calloc((strlen(db_path) + strlen(table) + 5), sizeof(char));
	strcat(tab_path, db_path);
	strcat(tab_path, table);
	strcat(tab_path, ".csv");
	return (tab_path);
}

void		create_table_file(char *table_path, t_table *table)
{
	return ;
}

/*
**	create_table
**
**	Creates a table csv file for the given database.
**
**	@param db:		Database name
**	@param table:	Table name
*/

void		create_table(char *db, t_table *table)
{
	struct stat	st;
	char		*table_path;
	char		*db_path;

	db_path = get_db_path(db);
	if (stat(db_path, &st) == -1)
	{
		printf("Error: Couldn't get table path. Database does not exist.\n");
		free(db_path);
		return ;
	}
	table_path = get_table_path(db_path, table->name);
	if (table_path == NULL)
	{
		printf("Error: Couldn't create table. Invalid table path.\n");
	}
	else if (stat(table_path, &st) == -1)
	{
		create_table_file(table_path, table);
	}
	free(db_path);
	free(table_path);
}

t_field		parse_field(char **field_data, int num_rows)
{
	t_field	field;
	int 	idx;

	idx = -1;
	while (++idx < NUM_FIELD_DATA)
	{
		if (idx == 0)
			field.name = strdup(field_data[idx]);
		else if (idx == 1 && strcmp(field_data[idx], FT_INT) == 0)
		{
			field.int_rows = (int*)calloc(num_rows, sizeof(int));
			field.data_type = FT_INT;
		}
		else if (idx == 1 && strcmp(field_data[idx], FT_STRING) == 0)
		{
			field.str_rows = (char**)calloc(num_rows, sizeof(char*));
			field.data_type = FT_STRING;
		}
		else if (idx == 2)
			field.size = atoi(field_data[idx]);
		else if (idx == 3)
			field.is_primary_key = atoi(field_data[idx]);
		else if (idx == 4)
			field.is_unique = atoi(field_data[idx]);
		else if (idx == 5)
			field.is_nullable = atoi(field_data[idx]);
		free(field_data[idx]);
	}
	// if (strcmp(field.data_type, "Int") == 0)
	// 	field.int_rows = (int*)calloc(num_rows, sizeof(int));
	// else if (strcmp(field.data_type, "String") == 0)
	// 	field.str_rows = (char**)calloc(num_rows, sizeof(char*));
	free(field_data);
	return field;
}

void		parse_row(char **row_data, t_table *tab_obj, int row_num)
{
	int 	idx;
	t_field	field;

	idx = -1;
	while (++idx < tab_obj->num_cols)
	{
		field = tab_obj->fields[idx];
		if (strcmp(field.data_type, "Int") == 0)
			field.int_rows[row_num] = atoi(row_data[idx]);
		else if (strcmp(field.data_type, "String") == 0)
			field.str_rows[row_num] = strdup(row_data[idx]);
		free(row_data[idx]);
	}
	free(row_data);
}

/*
**	parse_table_meta_data
**
**	Parses the meta data for the table. (ie. name, id counter, num_rows, etc.)
**
**	@param nth:		Nth line that we've read from the file. This tells us which
**					attribute we're on.
**	@param tab_obj:	Table object we're modifying.
**	@param buffer:	The line data we read from the file.
*/

void		parse_table_meta_data(int nth, t_table *tab_obj, char *buffer)
{
	char	**fields;
	char	**data_types;

	if (nth == 0)
		tab_obj->name = strdup(buffer);
	else if (nth == 1)
		tab_obj->id_counter = atoi(buffer);
	else if (nth == 2)
		tab_obj->num_rows = atoi(buffer);
	else if (nth == 3)
	{
		tab_obj->num_cols = atoi(buffer);
		tab_obj->fields = calloc(tab_obj->num_cols, sizeof(t_field));
	}
}

t_table		load_table(char *table_path, char *table_name)
{
	FILE    *entry_file;
	t_table	tab_obj;
	char	buffer[BUFF_SIZE];
	int		line;

	line = -1;
	entry_file = fopen(table_path, "rw");
	if (entry_file == NULL)
	{
		tab_obj.is_bad = 1;
		return tab_obj;
	}
	while (fgets(buffer, BUFF_SIZE, entry_file) != NULL)
	{
		// printf("%d\n", line);
		buffer[strcspn(buffer, "\n")] = 0;
		if (++line < 4)
			parse_table_meta_data(line, &tab_obj, buffer);
		else if (line < 4 + tab_obj.num_cols)
			tab_obj.fields[line - 4] = parse_field(ft_strsplit(buffer, ','), tab_obj.num_rows);
		else
			parse_row(ft_strsplit(buffer, ','), &tab_obj, line - 4 - tab_obj.num_cols);
	}
	fclose(entry_file);
	return tab_obj;
}

/*
**	load_tables
**
**	Gets all the table data for the database.
**
**	@param db_path:	Path to database
**	@return:		List of tables
*/

t_table		*load_tables(char *db_path, int num_tables)
{
	DIR				*dir_fd;
	struct dirent	*dir;
	t_table			*tables;
	char			*table_path;
	int				idx;

	idx = 0;
	if (!(dir_fd = opendir(db_path))) 
		return (NULL);
	tables = (t_table*)calloc(num_tables, sizeof(t_table));
	while ((dir = readdir(dir_fd))) 
	{
		if (strcspn(dir->d_name, "t_") != 0)
			continue;
		// printf("%s\n", dir->d_name);
		table_path = (char*)calloc(strlen(db_path) + strlen(dir->d_name) + 1,
			sizeof(char));
		strcat(table_path, db_path);
        strcat(table_path, dir->d_name);
		tables[idx++] = load_table(table_path, dir->d_name);
		free(table_path);
	}
	return (tables);
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
