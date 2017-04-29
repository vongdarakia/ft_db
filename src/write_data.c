/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   write_data.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 01:09:27 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/29 01:09:28 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*
**	write_fields
**
**	Append write all fields of a table to a file.
**
**	@param file:		File we're appending to.
**	@param fields:		Fields we're writing out.
**	@param num_fields:	Number of fields we're writing out.
*/

void	write_fields(FILE *file, t_field *fields, int num_fields)
{
	int		i;
	t_field f;

	i = -1;
	while (++i < num_fields)
	{
		f = fields[i];
		fprintf(file, "%s,%s,%d,%d,%d,%d\n",
			f.name, f.data_type, f.size, f.is_primary_key,
			f.is_unique, f.is_nullable);
	}
}

/*
**	write_rows
**
**	Append write all rows of a table to a file.
**
**	@param file:	File we're appending to.
**	@param table:	Table we're writing out.
*/

void	write_rows(FILE *file, t_table *table)
{
	int		r;
	int		c;
	t_field f;

	r = -1;
	while (++r < table->num_rows)
	{
		c = -1;
		while (++c < table->num_cols)
		{
			f = table->fields[c];
			if (f.data_type == FT_STRING)
				fprintf(file, "%s", f.str_rows[r]);
			else if (f.data_type == FT_INT)
				fprintf(file, "%d", f.int_rows[r]);
			if (c < table->num_cols - 1)
				fprintf(file, ",");
		}
		fprintf(file, "\n");
	}
}

/*
**	write_table
**
**	Writes the entire table to a file.
**
**	@param db:		Database name of the table.
**	@param table:	Table we're writing out.
*/

void	write_table(char *db, t_table *table)
{
	FILE	*file;
	char	*db_path;
	char	*table_path;

	db_path = get_db_path(db);
	table_path = get_table_path(db_path, table->name);
	file = fopen(table_path, "w");
	fprintf(file, "%s\n", table->name);
	fprintf(file, "%d\n", table->id_counter);
	fprintf(file, "%d\n", table->num_rows);
	fprintf(file, "%d\n", table->num_cols);
	write_fields(file, table->fields, table->num_cols);
	write_rows(file, table);
	fflush(file);
	fclose(file);
	free(db_path);
	free(table_path);
}

/*
**	write_to_table
**
**	Appends new data to the data file. Right now we can't do this.
**	We have to split the table meta data separate from the row data,
**	so that we don't have to rewrite the entire file every time since
**	the number of rows are always changing.
**
**	This should add the last table row to the file.
**
**	@param db:		Database name of the table.
**	@param table:	Table we're writing out.
*/

void	write_to_table(char *db, t_table *table)
{

}