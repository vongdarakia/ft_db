/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mfilipch <mfilipch@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:49:09 by mfilipch          #+#    #+#             */
/*   Updated: 2017/04/27 16:49:09 by mfilipch         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"


void	free_args(char **args)
{
	int	i;

	i = 0;
	if (args)
		while (args[i])
		{
			free(args[i]);
			i++;
		}
	free(args);	
}

/* 
** If DB in use and Table in use then
** Parsing query: get command and it's arguments, call appropriate function
** !Call table to file
** ?Might want to consider lower and upper case commands
*/

int parse_query(char **args, t_env *env)
{
	char	*arg;
	int		ret;
	int		i;

	arg = NULL;
	
	i = 0;
	arg = args[0];
	ret = 1;
	if (strcmp(arg, ADD) == 0 && args)
		ret = add(&(args[1]), env->tbl_in_use);
	else if (strcmp(arg, DELETE) == 0 && args)
		ret = del(&(args[1]), env->tbl_in_use);
	else if (strcmp(arg, UPDATE) == 0 && args)
		ret = upd(&(args[1]), env->tbl_in_use);
	if (ret == 0)
		write_table(env->db_in_use->name, env->tbl_in_use);
	return (ret);
}

/*
** -Display help or env content (database in use, table in use + content)
** -Choose/create database
** -Choose/create table
** !Create function: display_env
** !Create db and talbe functions take in arguments, depending on mangement should be provided
** ?Might want to consider lower and upper case commands
*/

int set_db_tbl(char **args, t_env *env)
{
	char	*arg;
	int		ret;
	t_table	t;

	arg = args[0];
	ret = 1;
	if (strcmp(arg, EXIT) == 0)
	{
		free_map(args);
		exit_program(env);
	}
	else if (strcmp(arg, HELP) == 0)
		ret = display_help();
	else if (strcmp(arg, DISPLAY) == 0)
		ret = display_env(env);
	else if (env->db_in_use && strcmp(arg, DISPLAY_TABLE) == 0)
		ret = display_tbl(args[1], env);
	else if (strcmp(arg, CREATE_DB) == 0)
		ret = create_db(args[1]);
	else if (strcmp(arg, USE_DB) == 0)
		ret = use_db(args[1], env);
	else if (env->db_in_use && strcmp(arg, CREATE_TABLE) == 0)
	{
		t = table(args[1]);
		ret = create_table(env->db_in_use->name, &t);
	}
	else if (env->db_in_use && strcmp(arg, USE_TABLE) == 0)
		ret = use_table(args[1], env);
	return (ret);
}

/* 
** Reading for STDIN
*/

int	read_input(t_env *env)
{
	size_t		ret;
	size_t	linecap;
	char	buffer[BUFF_SIZE];
	char	*line;
	char	**args;

	linecap = (size_t) BUFF_SIZE;
	line = buffer;
	bzero(line, linecap);
	printf(">> ");
	while ((ret = getline(&line, &linecap, stdin)) > 0)
	{
		line[ret - 1] = 0;
		if ((args = ft_strsplit(line, *SEP)))
		{
			if (set_db_tbl(args, env) && env->db_in_use && env->tbl_in_use)
				if (parse_query(args, env))
					call_error(ERR_Q);
			free_args(args);
		}
		else
			call_error(9);
		printf(">> ");
	}
	if (ret == -1)
		call_error(ERR_RET);
	return (0);
}
