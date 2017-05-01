/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   entry_queries.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:49:09 by mfilipch          #+#    #+#             */
/*   Updated: 2017/04/27 16:49:09 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

static int	check_types(char **args, t_table *table)
{
	int		i;
	char	*ptr;

	i = -1;
	while (*args && ++i < table->num_cols)
	{
		printf("arg: %s\n | field type: %s\n, col_num %d\n", *args, table->fields[i].data_type, i);
		if (table->fields[i].is_primary_key)
			continue ;
		else if (strcmp(table->fields[i].data_type, FT_INT) == 0
			&& (strtol(*args, &ptr, 10) == 0 && errno == EINVAL))
			return (1);
		else if (strcmp(table->fields[i].data_type, FT_INT) != 0 && 
			strcmp(table->fields[i].data_type, FT_STRING) != 0)
			return (1);
		args++;
	}
	if (*args)
		return (1);
	while (i < table->num_cols)
	{
		if (table->fields[i].is_primary_key == 0)
			return (1);
		i++;
	}
	table->num_rows++;
	return (0);
}

/*
** !Problem with memory reallocation
*/

int		add(char **args, t_table *table)
{
	int		i;
	char	*ptr;

	printf("Checking types\n");
	if (check_types(args, table) != 0)
		return (1);
	printf("Types are fine\n");
	i = -1;
	while (*args && ++i < table->num_cols)
	{
		if (strcmp(table->fields[i].data_type, FT_INT) == 0)
		{
			table->fields[i].int_rows = (int*)realloc(table->fields[i].int_rows,
				table->num_rows * sizeof(int));
			table->fields[i].int_rows[table->num_rows - 1] = (table->fields[i]
				.is_primary_key) ? ++(table->id_counter) : strtol(*args, &ptr, 10);
			if (table->fields[i].is_primary_key)
				continue ;
		}
		else if (strcmp(table->fields[i].data_type, FT_STRING) == 0)
		{
			table->fields[i].str_rows = (char**)realloc(
				table->fields[i].str_rows, table->num_rows * sizeof(char*));
			table->fields[i].str_rows[table->num_rows - 1] = strdup(*args);
		}
		args++;
	}	
	return (0);
}

/*
** Deletes field by row number
** !Delete by search args params
*/

int		del(char **args, t_table *table)
{
	int		i;
	int		ind;
	char	*ptr;

	if ((!(ind = strtol(*args, &ptr, 10)) && errno == EINVAL) || ind >= table->num_rows)
		return (1);
	i = -1;
	table->num_rows--;
	while (++i < table->num_cols)
		if (strcmp(table->fields[i].data_type, FT_INT) == 0)
		{
			if (ind < table->num_rows)
				memmove(&(table->fields[i].int_rows[ind]), &(table->fields[i].
				int_rows[ind + 1]), (table->num_rows - ind) * sizeof(int));
			table->fields[i].int_rows = (int*)realloc(
				table->fields[i].int_rows, table->num_rows * sizeof(int));
		}
		else if (strcmp(table->fields[i].data_type, FT_STRING) == 0)
		{
			if (ind < table->num_rows)
				memmove(&(table->fields[i].str_rows[ind]), &(table->fields[i].
				str_rows[ind + 1]), (table->num_rows - ind) * sizeof(char*));
			free(table->fields[i].str_rows[table->num_rows]);
			table->fields[i].str_rows = (char**)realloc(
				table->fields[i].str_rows, table->num_rows * sizeof(char*));
		}
	return (0);
}

/*
** !Need to write update function
*/

int		upd(char **args, t_table *table)
{
	return (0);
}