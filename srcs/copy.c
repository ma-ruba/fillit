int	ft_put_tetr(char **map, t_fig *fig, int map_size, int block)
{
	int		i;
	int		j;

	ft_find_position(map, fig->tetr_numb, &i, &j);
	while (block < 3)
	{
		if (map[i][j] == '.')
		{
			map[i][j] = fig->letter;
			while(block < 3)
			{
				if (j - fig->coord[block][1] >= 0 && j - fig->coord[block][1] < map_size && i - fig->coord[block][0] >= 0
					&& i - fig->coord[block][0] < map_size && map[i - fig->coord[block][0]][j - fig->coord[block][1]] == '.') 
				{	
					map[i - fig->coord[block][0]][j - fig->coord[block][1]] = fig->letter;
					block++;
				}
				else
				{
					ft_remoove_tetr(map, fig->tetr_numb);
					if (!(exept(map, &i, &j)))
						return (0);
					block = 0;
					break ;
				}
			}
		}
		else
			if (!(exept(map, &i, &j)))
				return (0);
	}
	return (1);
}

-----------------------------------------------

void	posit(char **map, char *position, int *i, int *j)
{
	*i = 0;
	*j = 0;

	while (map[*i])
	{
		while (map[*i][*j])
		{
			if (&map[*i][*j] == position) // ????
				return ;
			(*j)++;
		}
		(*i)++;
		*j = 0;
	}
}

int	norm(char **map, t_fig *fig, int *block, char *position)
{
	int	i;
	int	j;

	posit(map, position, &i, &j);
	map[i][j] = fig->letter;
	while(*block < 3)
	{
		if (j - fig->coord[*block][1] >= 0 && j - fig->coord[*block][1] < ft_map_size(map) && i - fig->coord[*block][0] >= 0
			&& i - fig->coord[*block][0] < ft_map_size(map) && map[i - fig->coord[*block][0]][j - fig->coord[*block][1]] == '.') 
		{	
			map[i - fig->coord[*block][0]][j - fig->coord[*block][1]] = fig->letter;
			(*block)++;
		}
		else
		{
			ft_remoove_tetr(map, fig->tetr_numb);
			if (!(exept(map, &i, &j)))
				return (0);
			*block = 0;
			break ;
		}
	}
	position = &map[i][j];
	return (1);
}

int	ft_put_tetr(char **map, t_fig *fig, int block)
{
	int		i;
	int		j;
	char	*position;

	ft_find_position(map, fig->tetr_numb, &i, &j);
	while (block < 3)
	{
		if (map[i][j] == '.')
		{
			position = &map[i][j];
			if (!(norm(map, fig, &block, position)))
				return (0);
			posit(map, position, &i, &j);
		}
		else
			if (!(exept(map, &i, &j)))
				return (0);
	}
	return (1);
}
