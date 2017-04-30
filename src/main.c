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

typedef struct s_point
{
	int x;
	int y;
}				t_point;

t_point getPoint(int x, int y)
{
	t_point p;
	p.x = x;
	p.y = y;
	return p;
}

// void	change(t_point pts)
// {
// 	pts->x = 0;
// 	pts->y = 0;
// }

// void print_mid_str(char *s, int width)
// {
// 	int left_spaces = width + strlen(s) / 2;
// 	int right_spaces = width - strlen(s) / 2;
//     printf("%*s%*s", left_spaces, s, right_spaces, "");
// }

int		main(int ac, char const *av[])
{
	t_database *db;
	// t_field field;
	// int i = 0;
	// int j = 0;
	// int k = 0;
	// t_point *pts;

	// printf("%lu\n", sizeof(db));

	// db = (t_database*)calloc(1, sizeof(t_database));
	// free(db);
	db = load_db("db");
	// printf("ROWS %d\n", db->tables->num_rows);
	display_table(db->tables);
	free_db(db);
	// print_mid_str("uno", 10);
	// f("something");
	// free_db(db);
	// printf("Do it... \n");
	// scanf ("%d", &k);
	// write_table(db->name, db->tables);
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
	// pts = (t_point*)calloc(1, sizeof(t_point));
    // t_point p = getPoint(1, 3);
    // // t_point *p2 = malloc(sizeof(t_point));
    // printf("%d %d\n", p.x, p.y);
    // printf("asdlfkjas;dlfj\n");
 //    p.x += 10;
 //    p.y += 10;
 //    printf("%d %d\n", p.x, p.y);
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
	return (0);
}
