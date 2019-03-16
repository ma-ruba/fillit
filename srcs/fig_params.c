#include "fillit.h"

void	ft_tetr_height(char *buff, t_fig *fig)
{
	int	count;
	int	block_count;

	count = 0;
	block_count = 0;
	while (*buff != '#')
		buff++;
	while (*buff != '\n')
		buff++;
	buff -= 4;
	while(buff)
	{
		buff++;
		count++;
		if (*buff == '#')
			block_count++;
		if (block_count == 4)
		{
			while (*buff != '\n')
			{
				buff++;
				count++;
			}
			fig->height = count / 5;
		}
	}
}

void    ft_tetr_width(char *buff, t_fig *fig)
{
        int width;

        width = 1;
        while (buff)
        {
            if (*buff == '#' && *(buff + 1) == '#' && *(buff + 5) == '#')
                fig->width = 2;
            buff++;
        }
        buff -= 21;
        while (buff)
        {
            if (*buff == '#' && *(buff + 1) == '#')
                width++;
            buff++;
        }
        fig->width = width;
}

void	ft_fig_coord(char *buff, t_fig *fig) // рассчитываются смещения 3ех решеток в тетримине относительно 1ой
{
	int	init_coord[2];
	int	count;
	int	block_count;

	count = 0;
	block_count = -1;
	while (*buff != '#')
	{
		count++;
		buff++;
	}
	init_coord[1] = count % 5; // column
	init_coord[0] = count / 5 + 1; // line
	while (buff)
	{
		buff++;
		count++;
		if (*buff == '#')
		{
			block_count++;
			fig->coord[block_count][0] = init_coord[0] - (count / 5 + 1);
			fig->coord[block_count][1] = init_coord[1] - (count % 5);
		}
	}
}
