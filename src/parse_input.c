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


/* 
** If DB in use and Table in use then
** Parsing query: get command and it's arguments, call appropriate function
** !Call table to file
** ?Might want to consider lower and upper case commands
*/

int parse_query(char *query, t_env *env)
{
	char	*arg;
	char	**args;
	int		ret;
	int		i;

	arg = NULL;
	if ((args = ft_strsplit(query, *SEP)))
		arg = args[0];
	i = 0;
	printf("query: %s\n", query);
	while (args[i])
	{
		printf("args ind: %d, arg: %s\n", i, args[i]);
		i++;
	}
	ret = 1;
	if (strcmp(arg, ADD) == 0 && args)
		ret = add(&(args[1]), env->tbl_in_use);
	else if (strcmp(arg, DELETE) == 0 && args)
		ret = del(&(args[1]), env->tbl_in_use);
	else if (strcmp(arg, UPDATE) == 0 && args)
		ret = upd(&(args[1]), env->tbl_in_use);
	i = 0;
	if (args)
		while (args[i])
		{
			free(args[i]);
			i++;
		}
	// free(args);
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

int set_db_tbl(char *query, t_env *env)
{
	char	*arg;
	int		ret;
	t_table	t;

	arg = strtok(query, SEP);
	ret = 1;
	if (strcmp(arg, HELP) == 0)
		ret = display_help();
	else if (strcmp(arg, DISPLAY) == 0)
		ret = display_env(env);
	else if (env->db_in_use && strcmp(arg, DISPLAY_TABLE) == 0)
		ret = display_tbl(strtok(NULL, SEP), env);
	else if (strcmp(arg, CREATE_DB) == 0)
		ret = create_db(strtok(NULL, SEP));
	else if (strcmp(arg, USE_DB) == 0)
		ret = use_db(strtok(NULL, SEP), env);
	else if (env->db_in_use && strcmp(arg, CREATE_TABLE) == 0)
	{
		t = table(strtok(NULL, SEP));
		ret = create_table(env->db_in_use->name, &t);
	}
	else if (env->db_in_use && strcmp(arg, USE_TABLE) == 0)
		ret = use_table(strtok(NULL, SEP), env);
	// free(arg);
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

	linecap = (size_t) BUFF_SIZE;
	// line = calloc(1, linecap);
	// printf("here\n");
	line = buffer;
	bzero(line, linecap);
	printf(">> ");
	while ((ret = getline(&line, &linecap, stdin)) > 0)
	{
		line[ret - 1] = 0;
		
		if (set_db_tbl(line, env) && env->db_in_use && env->tbl_in_use)
		{
			if (parse_query(line, env))
				call_error(ERR_Q);
		}
		// else
		// 	call_error(ERR_DB);
		bzero(line, ret);
		printf(">> ");
	}
	if (ret == -1)
		call_error(ERR_RET);
	// free(line);
	return (0);
}
