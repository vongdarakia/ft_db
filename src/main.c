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
	t_field field;
	int i;
	int j;
	int k;

	db = load_db("db");
	printf("Do it... \n");
	scanf ("%d", &k);
	write_table(db->name, db->tables);
	// printf("%s\n", db->name);
	// i = 0;
	// while (i < 1)
	// {
	// 	printf("table %s\n", db->tables[i].name);
	// 	j = -1;
	// 	while (++j < db->tables[i].num_cols)
	// 		printf("field %s\n", db->tables[i].fields[j].name);
	// 	j = -1;
	// 	while (++j < db->tables[i].num_rows)
	// 	{
			
	// 		k = -1;
	// 		while (++k < db->tables[i].num_cols)
	// 		{
	// 			field = db->tables[i].fields[k];
	// 			if (field.data_type == FT_STRING)
	// 				printf("row %s: %s\n", field.name, field.str_rows[j]);
	// 			if (field.data_type == FT_INT)
	// 				printf("row %s: %d\n", field.name, field.int_rows[j]);
	// 		}
	// 		// printf("field %s\n", field.name);
	// 	}
	// 	i++;
	// }
	// free_db(db);
	// create_db("db");
	// create_table("db", "table");

	// DIR* FD;
 //    struct dirent* in_file;
 //    FILE    *common_file;
 //    FILE    *entry_file;
 //    char    buffer[256];

    // t_point p = getPoint(1, 3);

    // printf("%d %d\n", p.x, p.y);
    /* Openiing common file for writing */
    // common_file = fopen(, "w");
    // if (common_file == NULL)
    // {
    //     fprintf(stderr, "Error : Failed to open common_file - %s\n", strerror(errno));

    //     return 1;
    // }

    // if (NULL == (FD = opendir ("Databases/db/"))) 
    // {
    //     fprintf(stderr, "Error : Failed to open input directory - %s\n", strerror(errno));
    //     fclose(common_file);

    //     return 1;
    // }
    // while ((in_file = readdir(FD))) 
    // {
    //     if (!strcmp (in_file->d_name, "."))
    //         continue;
    //     if (!strcmp (in_file->d_name, ".."))    
    //         continue;
    //     if (strcspn(in_file->d_name, "._") == 0)
    //     	continue;

        
    // //      Open directory entry file for common operation 
    //     char *path = (char*)calloc(strlen("Databases/db/") + strlen(in_file->d_name) + 1, sizeof(char));
    //     // char *path = strjoin("Databases/db/", in_file->d_name);
    //     strcat(path, "Databases/db/");
    //     strcat(path, in_file->d_name);
    //     printf("%s\n", path);
    //     entry_file = fopen(path, "rw");

    //     if (entry_file == NULL)
    //     {
    //         fprintf(stderr, "Error : Failed to open entry file - %s\n", strerror(errno));
    //         fclose(common_file);

    //         return 1;
    //     }

    //     while (fgets(buffer, 256, entry_file) != NULL)
    //     {
    //     	buffer[strcspn(buffer, "\n")] = 0;
    //         // printf("%s", buffer);
    //     }

    //     // fclose(entry_file);
    // }

    /* Don't forget to close common file before leaving */
    // fclose(common_file);

    return 0;
	return (0);
}
