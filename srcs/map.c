/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconwy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:11:20 by bconwy            #+#    #+#             */
/*   Updated: 2019/03/17 16:11:28 by bconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

/* Функции по работе с картой*/

char	**ft_make_map(int piece_count) // создается двумерная карта, где будут расставляться тетримины (норма) вроде работает
{
	char **map;
	int	count;
	int	map_size;

	map_size = 0;
	count = 0;
	while (map_size * map_size < piece_count * 4)
		map_size++;
	map = (char **)malloc((map_size + 1) * sizeof(char *));
	if (map == NULL)
		return (NULL);
    map[map_size] = NULL;
	while (count < map_size)
	{
		map[count] = ft_strnew(map_size);
		if (map[count] == NULL)
			return (NULL);
		count++;
	}
	count = -1;
	while (++count < map_size)
		ft_memset((void*)map[count], '.', map_size);
	return (map);
}

int	ft_map_size(char **map) // рассчитывается размер карты (норма) работает
{
	int	i;

	i = 0;
	while (map[i])
		i++;
	return (i);
}

void	ft_print_map(char **map) // печатается карта (норма)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (map[i])
	{
		while (map[i][j])
		{
			write(1, &map[i][j], 1);
			j++;
		}
		i++;
		j = 0;
		write(1, "\n", 1);
	}
}

void	ft_delete_map(char **map) // удаляет память под карту (норма)
{
	while (*map)
	{
		free((void*)*map);
		map++;
	}
}

char	**ft_enlarge_map(int map_size) // расширение карты после того как не удалось разместить тетримины (норма)
{
	char	**map;
	int		count;

	count = 0;
	map = (char **)malloc((map_size + 1) * sizeof(char *));
	map[map_size] = NULL;
	if (map == NULL)
		return (NULL);
	while (count < map_size)
	{
		map[count] = ft_strnew(map_size);
		if (map[count] == NULL)
			return (NULL);
		count++;
	}
	count = -1;
	while (++count < map_size)
		map[count] = ft_memset(map[count], '.', map_size);
	return (map);
}
