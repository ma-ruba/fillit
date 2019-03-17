/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconwy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:12:51 by bconwy            #+#    #+#             */
/*   Updated: 2019/03/17 16:12:56 by bconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Все доделано но не отлажено
*/

int	ft_fillit(char *file_name) // основной алгоритм (30 строк)
{
	char	**map;
	int		piece_count;
	t_fig	*struct_arr;
	int		count;
	int		map_size;

	count = 0;
	if (!(file_name))
        return (0);
	piece_count = ft_tetr_count(file_name);
	map = ft_make_map(piece_count);
	struct_arr = ft_struct_arr(file_name, piece_count);
	map_size = ft_map_size(map);
	while (count < piece_count)
	{
		if (!(ft_put_tetr(map, &struct_arr[count], map_size)) && count >= 0) /* если не удалось поставить надо перейти
		к предыдущей тетримине и попытаться поставить занаво, начиная со следуеще клетки */
			count--;
		else if (count < 0)
		{
			ft_delete_map(map);
			map = ft_enlarge_map(map_size);
			count = 0;
		}
		else
			count++;
	}
	ft_print_map(map);
	ft_delete_map(map);
	ft_delete_struct_arr(struct_arr);
	return (1);
}

void	ft_delete_struct_arr(t_fig *struct_arr) // удаляет память под массив структур (норма)
{
	free((void*)struct_arr);
}

t_fig	*ft_struct_arr(char *file_name, int piece_count) // создает массив структур (норма)
{
	char	buff[BUFF_SIZE];
	int		fd;
	t_fig	*struct_arr;
	int 	tetr_numb; // порядковый номер тетримины начиная с 0

	tetr_numb = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(struct_arr = (t_fig *)malloc((piece_count + 1) * sizeof(t_fig))))
		return (NULL);
	while (read(fd, buff, BUFF_SIZE) > 0)
	{
		struct_arr[tetr_numb].tetr_numb = tetr_numb;
		struct_arr[tetr_numb].letter = 'A' + tetr_numb;
		ft_fig_coord(buff, &struct_arr[tetr_numb++]);
	}
	if (close (fd) == -1)
		return (NULL);
	return (struct_arr);
}

void	ft_remoove_tetr(char **map, int tetr_numb) // удаление тетримины или ее части с карты (норма)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{               
			if (map[i][j] == 'A' + tetr_numb)
				map[i][j] = '.';
			j++;
		}                                  
		j = 0;
		i++;
	}	
}                                                                            

void	ft_find_position(char **map, int tetr_numb, int *i, int *j) /* нужно для определения координаты с которой функция ft_put_tetr()
будет находить новое положение для тетримины  (норма)*/ 
{
	while (map[*i])
	{
		while (map[*i][*j])
		{
			if (map[*i][*j] == 'A' + tetr_numb)
			{
				if (map[*i][*j + 1])
					(*j)++;
				else if (map[*i + 1])
				{
					(*i)++;
					*j = 0;
				}
				ft_remoove_tetr(map, tetr_numb);
				return ;
			}
			(*j)++;
		}
		*j = 0;
		(*i)++;
	}
	*i = 0;
	*j = 0;
}

int	ft_put_tetr(char **map, t_fig *fig, int map_size) // размещение тетримины на карте
{
	int		i;
	int		j;
	int		block_numb;

	i = 0;
	j = 0;
	block_numb = 0;
	ft_find_position(map, fig->tetr_numb, &i, &j);
	while (block_numb < 3)
	{
		if (map[i][j] == '.')
		{
			map[i][j] = fig->letter;
			while(block_numb < 3)
			{
				if (i + fig->coord[block_numb][1] > 0  && fig->coord[block_numb][0] + j < map_size && i + fig->coord[block_numb][1] > 0  && fig->coord[block_numb][1] + i < map_size)
				{	
					map[i + fig->coord[block_numb][1]][i + fig->coord[block_numb][1]] = fig->letter;
					block_numb++;
				}
				else
				{
					ft_remoove_tetr(map, fig->tetr_numb);
					if (map[i][j + 1])
						j++;
					else if (map[i])
					{
						i++;
						j = 0;
					}
					else
						return (0);
					block_numb = 0;
					break ;
				}
			}
		}
		else
		{
			if (map[i][j + 1])
				j++;
			else
			{
				i++;
				j = 0;
			}
		}
	}
	return (1);
}

