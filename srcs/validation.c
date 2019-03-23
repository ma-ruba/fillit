/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validation.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bconwy <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/03/17 16:17:24 by bconwy            #+#    #+#             */
/*   Updated: 2019/03/17 16:17:28 by bconwy           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "fillit.h"

// Проверка поданного в программу файла на валидность. Почти отлаженно кроме строки 114 

int ft_connect_tetr(char *buff) // проверяет что элементы тетримины касаются друг-друга
{
    int connect_count;
	int	i;

	connect_count = 0;
	i = 0;
	while (buff[i])
	{
		while (buff[i] != '#' && buff[i + 1])
			i++;
		if (!buff[i + 1])
			break ;
		if (buff[i + 1] == '#')
			connect_count++;
		if (buff[i - 1] == '#')
			connect_count++;
		if (buff[i + 5] == '#')
			connect_count++;
		if (buff[i - 5] == '#')
			connect_count++;
		i++;
	}
	if (connect_count != 6 && connect_count != 8)
		return (-1);
    return (1);
}

int	ft_valid_block_numb(char *buff) // проверяется что нет лишних символов, количество #
{
	int	block_count;
	int	i;

	i = 0;
	block_count = 0;
	while (buff[i] != '\n' || buff[i + 1] != '\n')
	{
		if (buff[i] != '\n' && buff[i] != '#' && buff[i] != '.')
			return (-1);
		if (buff[i] == '#')
			block_count++;
		i++;
	}
	if (block_count != 4)
			return (-1);
	return (1);
}

int	ft_valid_tetr_numb(char *buff) // 
{
	int	char_count;
	int line_count;
	int	i;
	
	i = 0;
	char_count = 0;
    line_count = 0;
	while (buff[i] != '\n')
	{
		while (buff[i] != '\n')
		{
			char_count++;
			i++;
		}
		if (char_count != 4) // проверяетя количество символов в строке
			return (-1);
		line_count++;
		char_count = 0;
		i++;
	}
	if (line_count != 4) // проверяетя количество строк
			return (-1);
	if (buff[20] != '\n' || buff[19] != '\0')
		return (-1);
	return (1);
}

int	ft_read_valid_file(char *file_name)
{
	int		fd;
	char	buff[BUFF_SIZE + 1];
	int		ret;
	int		tetr_count;

	tetr_count = 0;
    if (!(file_name))
        return (-1);
	fd = open(file_name, O_RDONLY);
    if (fd < 0)
		return (-1);
	while ((ret = read(fd, buff, BUFF_SIZE)) > 0)
	{
		buff[ret] = '\0';
        if (close(fd) == -1)
            return (-1);
		if (ft_valid_tetr_numb(buff) == -1 || ft_valid_block_numb(buff) == -1 || ft_connect_tetr(buff) == -1)
			return (-1);
		tetr_count++;
	}
	if (buff[BUFF_SIZE - 1] == '\n')
		return (-1);
    //if (close(fd) == -1) // Почему-то возвращвет -1
        //return (-1);
	close(fd);
	if (!(tetr_count >= 1 && tetr_count <= 26))
		return (-1);
	return (1);
}
