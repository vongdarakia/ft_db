/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 18:00:52 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/29 18:00:58 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

void		free_map(char **map)
{
	int i;

	i = 0;
	while (map[i])
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void		free_mapn(char **map, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		free(map[i]);
		i++;
	}
	free(map);
}

void		free_fields(t_field *fields, int num_fields, int num_rows)
{
	int i;

	i = -1;
	while (++i < num_fields)
	{
		if (strcmp(fields[i].data_type, FT_STRING) == 0)
			free_mapn(fields[i].str_rows, num_rows);
		if (strcmp(fields[i].data_type, FT_INT) == 0)
			free(fields[i].int_rows);
		free(fields[i].name);
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
	free(tables->fields);
	free(tables->name);
	free(tables);
}

void		free_db(t_database *db)
{
	free_tables(db->tables, db->num_tables);
	free(db->name);
	free(db);
}
