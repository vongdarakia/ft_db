/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_table.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: avongdar <vongdarakia@gmail.com>           +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/04/29 23:47:19 by avongdar          #+#    #+#             */
/*   Updated: 2017/04/29 23:47:21 by avongdar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_db.h"

int			print_mid_str(char *s, int width)
{
	int	left_spaces;
	int	right_spaces;

	left_spaces = width + strlen(s) / 2;
	right_spaces = width - strlen(s) / 2;
	return (printf("%*s%*s", left_spaces, s, right_spaces, ""));
}

int			print_mid_int(int d, int width)
{
	int	left_spaces;
	int	right_spaces;

	left_spaces = width + num_digits(d) / 2;
	right_spaces = width - num_digits(d) / 2;
	return (printf("%*d%*s", left_spaces, d, right_spaces, ""));
}

int			print_x(char *c, int x)
{
	int	num_char;
	int	i;

	num_char = 0;
	i = -1;
	while (++i < x)
	{
		num_char += printf("%s", c);
	}
	return (num_char);
}

void		print_rows(t_table *table)
{
	int		r;
	int		c;
	int		row_digits;
	t_field	*field;

	row_digits = num_digits(table->num_rows);
	row_digits = row_digits < 3 ? 3 : row_digits;
	r = -1;
	while (++r < table->num_rows)
	{
		c = -1;
		printf("| ");
		print_mid_int(r, row_digits);
		printf(" | ");
		while (++c < table->num_cols)
		{
			field = &table->fields[c];
			if (strcmp(field->data_type, FT_STRING) == 0)
				print_mid_str(field->str_rows[r], 12);
			else if (strcmp(field->data_type, FT_INT) == 0)
				print_mid_int(field->int_rows[r], 6);
			printf(" |");
		}
		printf("\n");
	}
}
