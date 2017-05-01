/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   db_queries.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:49:09 by mfilipch          #+#    #+#             */
/*   Updated: 2017/04/27 16:49:09 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

/*
** Find a table corresponding to a name and return table's address
*/

static t_table *find_table(char *tbl_name, t_env *env)
{
	int	i;

	i = 0;
	while (i < env->db_in_use->num_tables)
	{
		printf("Table name to compare %s\n", env->db_in_use->tables[i].name);
		if (strcmp(tbl_name, env->db_in_use->tables[i].name) == 0)
			return (&(env->db_in_use->tables[i]));
		i++;
	}
	return (NULL);
}

/*
** !Quering functions and it's usage should be displayed
*/

int	display_help(void)
{
	printf("\
Command line supports following commands:\n\
dsp\n\
- Displays stuff\n\n\
dsp_tbl [table_name]\n\
- By default displays table that is currently selected\n\
If table_name is specified displays corresponding table\n\n\
use_db database_name\n\
- Selects a db, the db should exist or should be created beforehand\n\n\
use_tbl table_name\n\
- Selects a table from the db if the db is selected and the table exists\n\n\
add value1, value2, ...\n\
- Adds a row into the table, values for every field should be entered.\n\
Primary_key (\'id\') field is autoincremented and sould not be specified\n\n\
del row_number\n\
- Deletes a row from the selected table, row index starts from 0\n\n\
upd row_number field1=value, field2=value, ...\n\
- Makes changes to the row_number entry changing values in specified fields\n\n\
exit\n\
- Exit the program\n");
	return (0);
}

/*
** Check for errors, find a table corresponding to a name and display it
** !Rename functions
** ?Probably merge  function with display_table
*/

int	display_tbl(char *tbl_name, t_env *env)
{
	t_table	*table;
	int		i;

	if (!tbl_name && !(env->tbl_in_use))
		return (1);
	else if (!tbl_name)
		table = env->tbl_in_use;
	else if (!(table = find_table(tbl_name, env)))
		return (1);
	display_table(table);
	return (0);
}

int	use_db(char *db_name, t_env *env)
{
	struct stat	st;

	if (!db_name)
		return (1);
	if (stat(DB_DIR, &st) == -1)
		mkdir(DB_DIR, 0755);
	if (stat(get_db_path(db_name), &st) == -1)
		return (1);
	if (env->db_in_use)
		free_db(env->db_in_use);
	if (!(env->db_in_use = load_db(db_name)))
		return (1);
	return (0);
}

int use_table(char *tbl_name, t_env *env)
{
	t_table *table;

	if (!tbl_name)
		return (1);
	table = find_table(tbl_name, env);
	if (!table)
		return (1);
	env->tbl_in_use = table;
	return (0);
}

int	exit_program(t_env *env)
{
	if (env->db_in_use)
		free_db(env->db_in_use);
	exit(0);
	return (0);
}
