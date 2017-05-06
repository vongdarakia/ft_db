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
# define BUFF_SIZE 1024
# define SEP " "
# define HELP "help"
# define SHOW "show"
# define TABLES "tables"
# define DATABASES "databases"
# define DISPLAY "dsp"
# define DISPLAY_TABLE "dsp_tbl"
# define CREATE "create"
# define CREATE_DB "cr_db"
# define CREATE_TABLE "cr_tbl"
# define USE_DB "use_db"
# define USE_TABLE "use_tbl"
# define ADD "add"
# define DELETE "del"
# define UPDATE "upd"
# define EXIT "exit"
# define ERR_Q 10
# define ERR_DB 11
# define ERR_RET 12
# define TBL_PREFIX "tabl_"
# include <sys/types.h>
# include <sys/stat.h>
# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <dirent.h>
# include <errno.h>

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

typedef struct	s_env
{
	t_database		*db_in_use;
	t_table			*tbl_in_use;
}				t_env;

char			*get_db_path(char *db);
char			*get_table_path(char *db, char *table);
char			*get_table_meta_path(char *db, char *table);

int				create(char **args, t_env *env);
int				create_db(char *db);
int				create_table(char **args, t_env *env);
int				create_table_file(char *db, t_table *table);

t_database		*load_db(char *db);
t_table			*load_tables(char *db_path, int num_tables);

void			free_tables(t_table *tables, int num_tables);
void			free_db(t_database *db);
void			free_map(char **map);
void			free_mapn(char **map, int num);

int				print_mid_str(char *s, int width);
int				print_mid_int(int d, int width);
int				print_x(char *c, int x);
void			print_rows(t_table *table);

int				num_digits(int num);
void			write_table(char *db, t_table *table);
void			display_table(t_table *table);
char			**ft_strsplit(char const *s, char c);
void			call_error(int err_code);

int				add(char **args, t_table *table);
int				del(char **args, t_table *table);
int				upd(char **args, t_table *table);
int				display_help(void);
int				display_tbl(char *tbl_name, t_env *env);
int				use_db(char *db_name, t_env *env);
int				use_table(char *tbl_name, t_env *env);
t_table			table(char *name);
int				display_env(t_env *env);
int				read_input(t_env *env);
int				exit_program(t_env *env);
int				show(char **args, t_env *env);

#endif
