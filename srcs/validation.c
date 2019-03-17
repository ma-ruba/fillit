#include "fillit.h"

// Проверка поданного в программу файла на валидность

int ft_connect_tetr(char *buff) // тут что-то не так
{
    int connect_count;

    while (buff)
    {
        connect_count = 0;
        while (!(*buff == '\n'))
        {
            while (*buff != '#' || (!(*buff == '\n' && *(buff + 1) == '\n')))
                buff++;
            if (*(buff + 1) == '#')
                connect_count++;
            if (*(buff - 1) == '#')
                connect_count++;
            if (*(buff + 5) == '#')
                connect_count++;
            if (*(buff - 5) == '#')
                connect_count++;
            buff++;
        }
        if (connect_count != 6 || connect_count != 8)
            return (-1);
        buff++;
    }
    return (1);
}

int	ft_valid_block_numb(char *buff)
{
	int	block_count;

	block_count = 0;
	while (buff)
	{
		while (!(*buff == '\n' && *(buff + 1) == '\n'))
		{
			if (*buff != '\n' || *buff != '#' || *buff != '.')
				return (-1);
			if (*buff == '#')
				block_count++;
			buff++;
		}
		if (block_count != 4)
				return (-1);
		buff++;
	}
	return (1);
}

int	ft_valid_tetr_numb(char *buff)
{
	int	tetr_count;
	int	char_count;
	int line_count;

    char_count = 0;
    line_count = 0;
    tetr_count = 0;
	while (buff)
	{
		while (!(*buff == '\n' && *buff == '\0'))
		{
			while (*buff != '\n')
			{
				buff++;
				char_count++;
			}
			if (char_count != 4)
				return (-1);
			line_count++;
			buff++;
		}
		if (line_count != 4)
				return (-1);
		tetr_count++;
        if (*buff == '\0')
            return (-1);
		buff++;
	}
	if (!(tetr_count >= 1 && tetr_count <= 26))
		return (-1);
	return (1);
}

int	ft_read_valid_file(char *file_name)
{
	int		fd;
	char	buff[BUFF_SIZE];
	int		ret;

    if (!(file_name))
        return (-1);
	fd = open(file_name, O_RDONLY);
    if (fd < 0 || fd > BUFF_SIZE)
		return (-1);
	if ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
        if (close(fd) == -1)
            return (-1);
		if (ft_valid_tetr_numb(buff) != 1 && ft_valid_block_numb(buff) != 1 && ft_connect_tetr(buff) != 1)
			return (-1);
		return (1);
	}
    if (close(fd) == -1)
        return (-1);
	return (-1);
}

int	ft_tetr_count(char *file_name) 
{
	int		fd;
	int		ret;
	char	buff[400];

	if (!(file_name))
        return (0);
	fd = open(file_name, O_RDONLY);
	if (fd < 0)
		return (0);
	if (!(ret = read(fd, buff, 546) > 0))
		return (0);
	if (close (fd) == -1)
		return (0);
	return (ret / 21);
}
