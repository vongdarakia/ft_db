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
#define SEP " "
#define HELP "HLP"
#define DISPLAY "DSP"
#define DISPLAY_TABLE "DSP_TBL"
#define CREATE_DB "CR_DB"
#define CREATE_TABLE "CR_TBL"
#define USE_DB "USE_DB"
#define USE_TABLE "USE_TBL"
#define ADD "ADD"
#define DELETE "DEL"
#define UPDATE "UPD"
#define ERR_Q 10
#define ERR_DB 11
#define ERR_RET 12

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
	if ((args = ft_strsplit(query, SEP)))
		arg = args[0];
	ret = 1;
	if (strcmp(arg, ADD) == 0 && args)
		ret = add(args, env->tbl_in_use);
	else if (strcmp(arg, DELETE) == 0 && args)
		ret = del(args, env->tbl_in_use);
	else if (strcmp(arg, UPDATE) == 0 && args)
		ret = upd(args, env->tbl_in_use);
	i = 0;
	if (args)
		while (args[i])
		{
			free(args[i]);
			i++;
		}
	free(args);
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

	arg = strtok(query, SEP);
	ret = 1;
	if (strcmp(arg, HELP) == 0)
		ret = display_help();
	else if (strcmp(arg, DISPLAY) == 0)
		ret = display_env(env);
	else if (strcmp(arg, DISPLAY_TABLE) == 0)
		ret = display_tbl(strtok(NULL, SEP), env);
	else if (strcmp(arg, CREATE_DB) == 0)
		ret = create_db(strtok(NULL, SEP));
	else if (strcmp(arg, USE_DB) == 0)
		ret = use_db(strtok(NULL, SEP), env);
	else if (env->db_in_use && strcmp(arg, CREATE_TABLE) == 0)
		ret = create_table(env->db_in_use, strtok(NULL, SEP));
	else if (env->db_in_use && strcmp(arg, USE_TABLE) == 0)
		ret = use_table(strtok(NULL, SEP), env);
	free(arg);
	return (ret);
}

/* 
** Reading for STDIN
*/

int	read_input(t_env *env)
{
	int		ret;
	int		linecap;
	char	*line;

	linecap = BUFF_SIZE;
	line = calloc(linecap, 1);
	while ((ret = getline(&line, &linecap, 0)) > 0)
	{
		if (env->db_in_use && env->tbl_in_use)
		{
			if (parse_query(line, env))
				call_error(ERR_Q);
		}
		else if (set_db_tbl(line, env))
			call_error(ERR_DB);
		bzero(line, linecap);
	}
	if (ret == -1)
		call_error(ERR_RET);
	free(line);
	return (0);
}
