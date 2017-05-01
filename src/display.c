#include "ft_db.h"

int	display_env(t_env *env)
{
	printf("Environment:\n");
	printf("Database: %s\n", env->db_in_use ? env->db_in_use->name : NULL);
	printf("Table: %s\n", env->tbl_in_use ? env->tbl_in_use->name : NULL);
	return 0;
}
