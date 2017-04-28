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
# define DB_DIR "Databases"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include "libft.h"

struct	s_field
{
	char	*name;
	char	*data_type;
	int		size;
	int		is_primary_key;
	int		is_unique;
}		t_field;

struct	s_table
{
	char			*name;
	struct s_field	*fields;
	int				id_counter;
	int				num_rows;
	int				num_fields;
}		t_table;

struct	s_database
{
	char			*name;
	struct s_table	*tables;
}		t_database;

char	*get_db_path(char *db);
void	create_db(char *db);
char	*get_table_path(char *db, char *table);
void	create_table(char *db, char *table);

#endif
