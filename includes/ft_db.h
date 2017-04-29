/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_db.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 23:01:29 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/27 23:01:32 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_DB_H
# define FT_DB_H
# define NUM_FIELD_DATA 6
# define DB_DIR "Databases"
# define FT_INT "Int"
# define FT_STRING "String"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <dirent.h>
# include <errno.h>
# include "libft.h"

typedef struct	s_field
{
	char	*name;
	char	*data_type;
	int		size;
	int		is_primary_key;
	int		is_unique;
	int		is_nullable;
	int		*int_rows;
	char	**str_rows;
}				t_field;

typedef struct	s_table
{
	char			*name;
	struct s_field	*fields;
	int				id_counter;
	int				num_rows;
	int				num_cols;
	int				is_bad;
}				t_table;

typedef struct	s_database
{
	char			*name;
	struct s_table	*tables;
	int				num_tables;
}				t_database;

char			*get_db_path(char *db);
void			create_db(char *db);
char			*get_table_path(char *db, char *table);
void			create_table(char *db, t_table *table);
t_database		*load_db(char *db);
t_table			*load_tables(char *db_path, int num_tables);
void			free_tables(t_table *tables, int num_tables);
void			free_db(t_database *db);
void			write_table(char *db, t_table *table);

#endif
