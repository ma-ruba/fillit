#include "fillit.h"

int	main(int argc, char **argv)
{
	if (argc == 2)
	{
		if (ft_read_valid_file(argv[1]) != 1)
        {
            write(1, "error\n", 6);
            return (0);
        }
		ft_fillit(argv[1]);
	}
	return (0);
}
