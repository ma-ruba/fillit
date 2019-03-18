/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fig_params.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconwy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:11:01 by bconwy            #+#    #+#             */
/*   Updated: 2019/03/17 16:11:07 by bconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

// Не вылетает, но не понимаю что записывается в структуру в координаты

void	ft_fig_coord(char *buff, t_fig *fig) // рассчитываются смещения 3ех решеток в тетримине относительно 1ой 
{
	int	init_coord[2];
	int	count;
	int	block_count;
	int	i;

	count = 1;
	i = 0;
	block_count = -1;
	while (buff[i] != '#')
	{
		count++;
		i++;
	}
	init_coord[1] = count % 5; // column
	init_coord[0] = count / 5 + 1; // line
	while (buff[i])
	{
		i++;
		count++;
		if (buff[i] == '#')
		{
			block_count++;
			fig->coord[block_count][0] = init_coord[0] - (count / 5 + 1);
			fig->coord[block_count][1] = init_coord[1] - (count % 5);
		}
	}
}
