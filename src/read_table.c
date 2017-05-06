/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_table.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 03:17:05 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/29 03:17:06 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

t_field		parse_field(char **data, int num_rows)
{
	t_field	field;
	int		idx;

	idx = -1;
	while (++idx < NUM_FIELD_DATA)
		if (idx == 0)
			field.name = strdup(data[idx]);
		else if (idx == 1 && strcmp(data[idx], FT_INT) == 0)
			field.int_rows = (int*)calloc(num_rows, sizeof(int));
		else if (idx == 1 && strcmp(data[idx], FT_STRING) == 0)
			field.str_rows = (char**)calloc(num_rows, sizeof(char*));
		else if (idx == 2)
			field.size = atoi(data[idx]);
		else if (idx == 3)
			field.is_primary_key = atoi(data[idx]);
		else if (idx == 4)
			field.is_unique = atoi(data[idx]);
		else if (idx == 5)
			field.is_nullable = atoi(data[idx]);
	field.data_type = strcmp(data[1], FT_STRING) == 0 ? FT_STRING : FT_INT;
	free_map(data);
	return (field);
}

void		parse_row(char **row_data, t_table *tab_obj, int row_num)
{
	int		idx;
	t_field	field;

	idx = -1;
	while (++idx < tab_obj->num_cols)
	{
		field = tab_obj->fields[idx];
		if (strcmp(field.data_type, "Int") == 0)
			field.int_rows[row_num] = atoi(row_data[idx]);
		else if (strcmp(field.data_type, "String") == 0)
			field.str_rows[row_num] = strdup(row_data[idx]);
	}
	free_map(row_data);
}

/*
**	parse_table_meta_data
**
**	Parses the meta data for the table. (ie. name, id counter, num_rows, etc.)
**
**	@param dbp:		Database path
**	@param nth:		Nth line that we've read from the file. This tells us which
**					attribute we're on.
**	@param tab:		Table object we're modifying.
**	@param bf:		The line data we read from the file.
*/

void		parse_table_meta_data(char *dbp, int nth, t_table *tab, char *bf)
{
	FILE	*file;
	char	*meta_path;

	if (nth == 0)
		tab->name = strdup(bf);
	else if (nth == 1)
		tab->id_counter = atoi(bf);
	else if (nth == 2)
		tab->num_rows = atoi(bf);
	else if (nth == 3)
	{
		tab->num_cols = atoi(bf);
		tab->fields = (t_field*)calloc(tab->num_cols, sizeof(t_field));
	}
}

t_table		load_table(char *db_path, char *table_path, char *table_name)
{
	FILE	*file;
	t_table	t;
	char	bf[BUFF_SIZE];
	char	*line;
	int		nth;

	nth = -1;
	file = fopen(table_path, "r");
	if (file == NULL)
	{
		t.is_bad = 1;
		fclose(file);
		return (t);
	}
	while ((line = fgets(bf, BUFF_SIZE, file)) != NULL)
	{
		bf[strcspn(bf, "\n")] = 0;
		if (++nth < 4)
			parse_table_meta_data(db_path, nth, &t, bf);
		else if (nth < 4 + t.num_cols)
			t.fields[nth - 4] = parse_field(ft_strsplit(bf, ','), t.num_rows);
		else
			parse_row(ft_strsplit(bf, ','), &t, nth - 4 - t.num_cols);
	}
	fclose(file);
	return (t);
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
	char			*res;

	idx = 0;
	if (!(dir_fd = opendir(db_path)))
		return (NULL);
	tables = (t_table*)calloc(num_tables + 1, sizeof(t_table));
	while ((dir = readdir(dir_fd)))
	{
		res = strstr(dir->d_name, TBL_PREFIX);
		if (res - dir->d_name != 0)
			continue;
		table_path = (char*)calloc(strlen(db_path) + strlen(dir->d_name) + 1,
			sizeof(char));
		strcat(table_path, db_path);
		strcat(table_path, dir->d_name);
		tables[idx++] = load_table(db_path, table_path, dir->d_name);
		free(table_path);
	}
	closedir(dir_fd);
	return (tables);
}
