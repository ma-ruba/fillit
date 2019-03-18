#ifndef FILLIT_H
# define FILLIT_H

# include <fcntl.h>
# include <unistd.h>
# include <stdlib.h>
# include "libft.h"

# define BUFF_SIZE 21

typedef struct	s_fig
{
	char			coord[3][2];
	int				tetr_numb;
	char			letter;
}					t_fig;

int 	ft_connect_tetr(char *buff);
int		ft_valid_block_numb(char *buff);
int		ft_valid_tetr_numb(char *buff);
int		ft_read_valid_file(char *file_name);
int		ft_tetr_count(char *file_name);
void	ft_fig_coord(char *buff, t_fig *fig);
char	**ft_make_map(int piece_count);
int		ft_map_size(char **map);
void	ft_print_map(char **map);
int		ft_fillit(char *file_name);
void	ft_delete_struct_arr(t_fig *struct_arr);
void	ft_delete_map(char **map);
t_fig	*ft_struct_arr(char *file_name, int piece_count);
t_fig	*ft_create_struct(char *buff, int tetr_numb);
void	ft_remoove_tetr(char **map, int tetr_numb);
char	**ft_enlarge_map(int map_size);
void	ft_find_position(char **map, int tetr_numb, int *i, int *j);
int		ft_put_tetr(char **map, t_fig *fig, int map_size);

#endif
