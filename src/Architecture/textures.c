/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   textures.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/03/02 19:12:07 by nalfonso          #+#    #+#             */
/*   Updated: 2026/03/05 23:11:36 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

void	*ft_load(t_game *g, char *path)
{
	void	*img;
	int		w;
	int		h;

	w = g->width;
	h = g->heigth;
	img = mlx_xpm_file_to_image(g->mlx, path, &w, &h);
	if (!img)
	{
		ft_printf("Error\nFailed to load texture: %s\n", path);
		return (NULL);
	}
	return (img);
}

int	ft_load_textures(t_game *g)
{
	g->img_wall = ft_load(g, "Textures/wall.xpm");
	g->img_floor = ft_load(g, "Textures/floor.xpm");
	g->img_player = ft_load(g, "Textures/player.xpm");
	g->img_collect = ft_load(g, "Textures/collectible.xpm");
	g->img_exit = ft_load(g, "Textures/exit.xpm");
	if (!g->img_wall || !g->img_floor || !g->img_player
		|| !g->img_collect || !g->img_exit)
		return (1);
	return (0);
}
