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

static t_table	*find_table(char *tbl_name, t_env *env)
{
	int	i;

	i = 0;
	if (tbl_name == NULL)
		return (NULL);
	while (i < env->db_in_use->num_tables)
	{
		if (strcmp(tbl_name, env->db_in_use->tables[i].name) == 0)
			return (&(env->db_in_use->tables[i]));
		i++;
	}
	printf("Error: Couldn't find table\n");
	return (NULL);
}

/*
** !Quering functions and it's usage should be displayed
*/

int				display_help(void)
{
	printf("\
Command line supports the following commands:\n\
dsp\n\
- Displays current database and table that are in use\n\n\
dsp_tbl [table_name]\n\
show databases\n\
- List databases you can use.\n\n\
show tables\n\
- Shows tables you can use, but a database must first be in use.\n\n\
dsp_tbl [table_name]\n\
- By default, it displays selected table's contents.\n\
If table_name is specified, it will display the specified table\n\n\
use_db database_name\n\
- Selects a db, the db should exist or should be created beforehand\n\n\
create table table_name field1:type field2:type ...\n\
- Creates a table given a name and fields with their datatypes.\n\
There are two datatypes allowed at the moment: Int and String.\n\n\
use_tbl table_name\n\
- Selects a table from the db if the db is selected and the table exists\n\n\
add value1, value2, ...\n\
- Adds a row into the table, values for every field should be entered.\n\
Primary_key (\'id\') field is auto incremented and should not be specified\n\n\
For ex. For a table with the fields: id, first, last, age\n\
\t>> add Xavier Niel 49\n\n\
del row_number\n\
- Deletes a row from the selected table, row index starts from 0\n\n\
upd row_number field1=value, field2=value, ...\n\
- Makes changes to the specified fields of the entry \
for the specified row_number\n\n\
exit\n\
- Exit the program\n");
	return (0);
}

/*
** Check for errors, find a table corresponding to a name and display it
** !Rename functions
** ?Probably merge  function with display_table
*/

int				display_tbl(char *tbl_name, t_env *env)
{
	t_table	*table;

	if (!tbl_name && !(env->tbl_in_use))
		return (1);
	else if (!tbl_name)
		table = env->tbl_in_use;
	else if (!(table = find_table(tbl_name, env)))
		return (1);
	display_table(table);
	return (0);
}

int				use_db(char *db_name, t_env *env)
{
	struct stat	st;
	char		*db_path;

	if (!db_name)
		return (1);
	if (stat(DB_DIR, &st) == -1)
		mkdir(DB_DIR, 0755);
	db_path = get_db_path(db_name);
	if (stat(db_path, &st) == -1)
	{
		free(db_path);
		return (1);
	}
	free(db_path);
	if (env->db_in_use)
		free_db(env->db_in_use);
	if (!(env->db_in_use = load_db(db_name)))
		return (1);
	return (0);
}

int				use_table(char *tbl_name, t_env *env)
{
	t_table	*table;

	if (!tbl_name)
		return (1);
	table = find_table(tbl_name, env);
	if (!table)
		return (1);
	env->tbl_in_use = table;
	return (0);
}

int				show_databases(t_env *env)
{
	DIR				*dir_fd;
	struct dirent	*dir;
	int				idx;

	if (!(dir_fd = opendir(DB_DIR)))
	{
		printf("Error: There isn't a database repository.\n");
		return (1);
	}
	idx = printf("\n       Databases       \n");
	print_x("-", idx - 2);
	printf("\n");
	idx = 0;
	while ((dir = readdir(dir_fd)))
	{
		if (strstr(dir->d_name, ".") - dir->d_name == 0)
			continue;
		printf("%d:\t%s\n", ++idx, dir->d_name);
	}
	printf("\n");
	closedir(dir_fd);
	return (0);
	return (0);
}

int				show_tables(char **args, t_env *env)
{
	DIR				*dir_fd;
	struct dirent	*dir;
	char			*db_path;
	int				idx;

	if (!env->db_in_use)
	{
		printf("Error: a database must be in use first.\n");
		return (1);
	}
	db_path = get_db_path(env->db_in_use->name);
	dir_fd = opendir(db_path);
	idx = printf("\n       %s Tables       \n", env->db_in_use->name);
	print_x("-", idx - 2);
	printf("\n");
	idx = 0;
	while ((dir = readdir(dir_fd)))
	{
		if (strstr(dir->d_name, TBL_PREFIX) - dir->d_name != 0)
			continue;
		if (strlen(dir->d_name) - 4 > 0)
			dir->d_name[strlen(dir->d_name) - 4] = 0;
		printf("%d:\t%s\n", ++idx, dir->d_name);
	}
	printf("\n");
	free(db_path);
	closedir(dir_fd);
	return (0);
}

int				show(char **args, t_env *env)
{
	int len;

	len = 0;
	while (args[len])
		len++;
	if (len == 1 && args[0] != 0)
	{
		if (strcmp(args[0], TABLES) == 0
			|| strcmp(args[0], "tbls") == 0)
			return (show_tables(args, env));
		else if (strcmp(args[0], DATABASES) == 0
			|| strcmp(args[0], "dbs") == 0)
			return (show_databases(env));
	}
	return (1);
}

t_field			create_field(char *name, char *data_type)
{
	t_field	f;

	f.name = strdup(name);
	f.str_rows = NULL;
	f.int_rows = NULL;
	if (strcmp(data_type, FT_STRING) == 0)
	{
		f.data_type = FT_STRING;
		f.str_rows = (char**)calloc(1, sizeof(char*));
		f.size = 32;
	}
	else
	{
		f.data_type = FT_INT;
		f.int_rows = (int*)calloc(1, sizeof(int));
		f.size = 0;
	}
	f.is_primary_key = strcmp(name, "id") == 0 ? 1 : 0;
	f.is_unique = f.is_primary_key ? 1 : 0;
	f.is_nullable = 0;
	return (f);
}

int				create_table(char **args, t_env *env)
{
	int		i;
	int		j;
	char	**field;
	char	*db;
	char	*tbl;
	int		num_fields;
	t_table	t;

	i = 0;
	while (args[i])
		i++;
	if (i < 1)
		printf("Error: Table needs a name.\n");
	else if (i < 2)
		printf("Error: Table needs at least one field.\n");
	else
	{
		num_fields = i - 1;
		i = 0;
		j = -1;
		t = table(args[i]);
		t.num_cols += num_fields;
		t.num_rows = 0;
		t.fields = (t_field*)malloc(sizeof(t_field) * t.num_cols);
		while (args[++i])
		{
			field = ft_strsplit(args[i], ':');
			if (!field || (field && (!field[0] || !field[1])))
			{
				printf("Error: Invalid field structure.\n");
				free(t.fields);
				free_map(field);
				return (1);
			}
			else if (strcmp(field[1], FT_STRING) == 0
				|| strcmp(field[1], FT_INT) == 0)
			{
				if (strcmp(field[0], "id") == 0)
				{
					printf("Error: Invalid field name. Can't use id.\n");
					free(t.fields);
					free_map(field);
					return (1);
				}
				if (++j == 0)
				{
					t.fields[j] = create_field("id", FT_INT);
					t.fields[j++].is_unique = 0;
				}
				t.fields[j] = create_field(field[0], field[1]);
			}
			else
			{
				printf("Error: Invalid field datatype. Use Int or String.\n");
				free(t.fields);
				free_map(field);
				return (1);
			}
			free_map(field);
		}
		create_table_file(env->db_in_use->name, &t);
		db = strdup(env->db_in_use->name);
		tbl = env->tbl_in_use ? strdup(env->tbl_in_use->name) : NULL;
		free_db(env->db_in_use);
		env->db_in_use = load_db(db);
		env->tbl_in_use = find_table(tbl, env);
		free(db);
		free(tbl);
		return (0);
	}
	return (1);
}

int				create(char **args, t_env *env)
{
	int len;

	len = 0;
	while (args[len])
		len++;
	if (len >= 1 && args[0] != 0)
	{
		if (strcmp(args[0], TABLES) == 0
			|| strcmp(args[0], "table") == 0)
			return (create_table(args + 1, env));
	}
	return (1);
}

int				exit_program(t_env *env)
{
	if (env->db_in_use)
		free_db(env->db_in_use);
	exit(0);
	return (0);
}
