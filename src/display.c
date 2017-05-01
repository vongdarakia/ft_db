#include "ft_db.h"

int	display_env(t_env *env)
{
	printf("--- Environment ---\n");
	printf("Database:\t%s\n", env->db_in_use ? env->db_in_use->name : NULL);
	printf("Table:\t\t%s\n", env->tbl_in_use ? env->tbl_in_use->name : NULL);
	return 0;
}
