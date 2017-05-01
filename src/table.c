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

t_table		table(char *name)
{
	t_table t;

	t.name = name;
	t.id_counter = 10;
	t.num_rows = 0;
	t.num_cols = 1;
	t.is_bad = 0;

	return t;
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

char		*get_table_path(char *db_path, char *table)
{
	char		*tab_path;

	tab_path = calloc((strlen(db_path) + strlen(table) + 10), sizeof(char));
	strcat(tab_path, db_path);
	strcat(tab_path, "tabl_");
	strcat(tab_path, table);
	strcat(tab_path, ".csv");
	return (tab_path);
}

char	*get_table_meta_path(char *db_path, char *table)
{
	char		*tab_path;

	tab_path = calloc((strlen(db_path) + strlen(table) + 10), sizeof(char));
	strcat(tab_path, db_path);
	strcat(tab_path, "meta_");
	strcat(tab_path, table);
	strcat(tab_path, ".csv");
	return tab_path;
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

int			num_digits(int num)
{
	int	digits;

	digits = 1;
	while (num / 10)
	{
		digits += 1;
		num /= 10;
	}
	return (digits);
}

void		display_table(t_table *table)
{
	int		c;
	t_field	*field;
	int		num_char;

	c = num_digits(table->num_rows);
	c = c < 3 ? 3 : c;
	num_char = printf("| ");
	num_char += print_mid_str("Row", c);
	num_char += printf(" | ");
	c = -1;
	while (++c < table->num_cols)
	{
		field = &table->fields[c];
		if (strcmp(field->data_type, FT_STRING) == 0)
			num_char += print_mid_str(field->name, 12);
		else if (strcmp(field->data_type, FT_INT) == 0)
			num_char += print_mid_str(field->name, 6);
		num_char += printf(" |");
	}
	printf("\n");
	print_x("-", num_char);
	printf("\n");
	print_rows(table);
}
