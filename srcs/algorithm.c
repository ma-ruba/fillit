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

int	ft_fillit(char *file_name)
{
	char	**map;
	int		piece_count;
	t_fig	*struct_arr;
	int		count;
	int		block;

	count = 0;
	block = 0;
	piece_count = ft_tetr_count(file_name);
	map = ft_make_map(piece_count);
	struct_arr = ft_struct_arr(file_name, piece_count);
	while (count < piece_count)
	{
		if (count >= 0 && !(ft_put_tetr(map, &struct_arr[count], block)))
			count--;
		else if (count < 0)
			exeption(&map, &count);
		else
			count++;
	}
	ft_print_map(map);
	ft_delete_map(map);
	ft_delete_struct_arr(struct_arr);
	return (1);
}

void	exeption(char ***map, int *count)
{
	int		map_size;

	map_size = ft_map_size(*map);
	ft_delete_map(*map);
	*map = ft_enlarge_map(map_size + 1);
	*count = 0;
}

void	ft_delete_struct_arr(t_fig *struct_arr)
{
	free((void*)struct_arr);
}

t_fig	*ft_struct_arr(char *file_name, int piece_count)
{
	char	buff[BUFF_SIZE + 1];
	int		fd;
	t_fig	*struct_arr;
	int 	tetr_numb;
	int		ret;

	tetr_numb = 0;
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (NULL);
	if (!(struct_arr = (t_fig *)malloc((piece_count + 1) * sizeof(t_fig))))
		return (NULL);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
		struct_arr[tetr_numb].tetr_numb = tetr_numb;
		struct_arr[tetr_numb].letter = 'A' + tetr_numb;
		ft_fig_coord(buff, &struct_arr[tetr_numb++]);
	}
	if (close (fd) == -1)
		return (NULL);
	return (struct_arr);
}

void	ft_remoove_tetr(char **map, int tetr_numb)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i] && i < (int)ft_strlen(map[0]))
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

void	norm(char **map, int *i, int *j)
{
	if (map[*i][*(j + 1)])
		(*j)++;
	else if (map[*(i + 1)])
	{
		(*i)++;
		*j = 0;
	}
	else
	{
		*i = 0;
		*j = 0;
	}
}

void	ft_find_position(char **map, int tetr_numb, int *i, int *j)
{
	while (map[*i] && *i < (int)ft_strlen(map[0]))
	{
		while (map[*i][*j] && *i < (int)ft_strlen(map[0]))
		{
			if (map[*i][*j] == 'A' + tetr_numb)
			{
				norm(map, i, j);
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

int	norma(char **map, t_fig *fig, int *block, t_cor *cor)
{
	cor->size = ft_map_size(map);
	if (map[cor->i[0]][cor->j[0]] == '.')
	{
		map[cor->i[0]][cor->j[0]] = fig->letter;
		while(*block < 3)
		{
			if (cor->j[0] - fig->coord[*block][1] >= 0 && cor->j[0] - fig->coord[*block][1] < cor->size
				&& cor->i[0] - fig->coord[*block][0] >= 0 && cor->i[0] - fig->coord[*block][0] < cor->size
				&& map[cor->i[0] - fig->coord[*block][0]][cor->j[0] - fig->coord[*block][1]] == '.') 
			{	
				map[cor->i[0] - fig->coord[*block][0]][cor->j[0] - fig->coord[*block][1]] = fig->letter;
				(*block)++;
			}
			else
			{
				ft_remoove_tetr(map, fig->tetr_numb);
				if (!(exept(map, cor->i, cor->j)))
					return (0);
				*block = 0;
				return (1);
			}
		}
	}
	return (3);
}

int	ft_put_tetr(char **map, t_fig *fig, int block)
{
	int		i;
	int		j;
	t_cor	cor;

	i = 0;
	j = 0;
	cor.i = &i;
	cor.j = &j;
	ft_find_position(map, fig->tetr_numb, &i, &j);
	while (block < 3)
	{
		if (!(norma(map, fig, &block, &cor)))
			return (0);
		if (norma(map, fig, &block, &cor) == 3)
		{
			if (!(exept(map, &i, &j)))
				return (0);
		}
	}
	return (1);
}

int	exept(char **map, int *i, int *j)
{
	if (map[*i][*j + 1])
		(*j)++;
	else if (map[*i + 1])
	{
		(*i)++;
		*j = 0;
	}
	else
		return (0);
	return (1);
}

int	ft_tetr_count(char *file_name)
{
	int		fd;
	int		ret;
	char	buff[400];
	int		res;

	if (!(file_name))
        return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	ret = read(fd, buff, 400);
	if (close (fd) == -1)
		return (0);
	res = ret / 21 + 1;
	return (res);
}
