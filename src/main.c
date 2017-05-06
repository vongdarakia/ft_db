/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <avongdar@student.42.us.org>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/27 16:49:09 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/27 16:49:09 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int		main(int ac, char const *av[])
{
	t_database *db;
	t_env env;

	env.db_in_use = NULL;
	env.tbl_in_use = NULL;
	env.db_in_use = load_db("db");
	// env.tbl_in_use = env.db_in_use->tables;
	read_input(&env);
	free(env.db_in_use);

	// *** FREE MEMORY TEST
	// int size = 10;
	// int newSize = size - 2;
	// char **strs = malloc(sizeof(char*) * size);
	// int i = 0;

	// while (i < size)
	// {
	// 	strs[i] = strdup("Hello");
	// 	// strs[i] = malloc(sizeof(char) * size);
	// 	// itoa(i, strs[i], 10);
	// 	// sprintf(strs[i], "%d", i);
	// 	// printf("%s ", strs[i]);
	// 	i++;
	// }
	// printf("\n");
	// // printf("size %lu\n", sizeof(char*));
	// int idx = size / 2;
	// free(strs[idx]);
	// memmove(&(strs[idx]), &(strs[idx + 1]), (newSize + 1 - idx) * sizeof(char*));
	// // free(strs[newSize + 1]);


	// idx -= 1;
	// free(strs[idx]);
	// memmove(&(strs[idx]), &(strs[idx + 1]), (newSize - idx) * sizeof(char*));
	// // free(strs[newSize]);

	// i = 0;
	// while (i < newSize)
	// {
	// 	printf("%s ", strs[i++]);
	// }
	// printf("\n");
	// // free(strs[newSize]);
	// // free(strs[newSize + 1]);
	// strs = realloc(strs, sizeof(char*) * (newSize));
	
	// free_mapn(strs, newSize);

	return (0);
}
