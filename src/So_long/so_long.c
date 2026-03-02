/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:07:45 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/01 23:53:53 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../hdr/so_long.h"

int main(int ac, char **av)
{
    int   fd;
    t_map m;

    if (ac != 2)
        return (write(2, "Error\nUsage: ./so_long <map.ber>\n", 34), 1);

    fd = open(av[1], O_RDONLY);
    if (fd < 0)
        return (perror("open"), 1);

    if (ft_read_map_gnl(fd, &m))
        return (write(2, "Error\nInvalid map\n", 18), close(fd), 1);

    close(fd);

    if (ft_check_walls(&m))
        return (write(2, "Error\nMap not closed by walls\n", 30), 1);
	
	else if (ft_check_reachable(&m))
		return (write(2, "Error\nMap is not reacheable\n", 29), 1);
    return 0;
}

