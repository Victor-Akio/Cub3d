/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 22:12:54 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/30 04:02:43 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int					ft_init2(t_all *all)
{
	if (all->img.w == 0)
		all->img.w = 600;
	if (all->img.h == 0)
		all->img.h = 600;
	all->player.dist = ((double)(all->img.w) / 2.0) /
		tan((all->img.fov / 2) * RADIAN);
	return (1);
}

void				ft_init(t_all *all)
{
	all->map.h = -1;
	all->map.w = -1;
	all->map.map = NULL;
	all->img.img = NULL;
	all->win = NULL;
	all->img.addr = NULL;
	all->img.w = 0;
	all->img.h = 0;
	all->img.fov = 66;
	all->rotation = 5;
	all->walk = 0.20;
	all->color_c = -1;
	all->color_f = -1;
	all->rgb_f[0] = -1;
	all->rgb_c[0] = -1;
	all->player.pos.x = 0;
	all->player.pos.y = 0;
	all->player.dir.x = 0;
	all->player.dir.y = 1;
	all->tex = NULL;
	all->sprites = NULL;
	all->ray.buffer = NULL;
}

int					tex_init(t_all *all)
{
	int			i;

	i = 0;
	all->tex = (t_tex *)ft_calloc(5, sizeof(t_tex));
	while (i < 5)
	{
		if (!(load_tex(all, all->file.keys[i], i)))
			return (0);
		i++;
	}
	return (1);
}

void				window_init(t_all *all, t_img *img)
{
	validatescreen(all);
	all->win = mlx_new_window(all->mlx, img->w, img->h, GAME_TITLE);
	img->img = mlx_new_image(all->mlx, all->map.w, all->map.h);
	img->addr = mlx_get_data_addr(img->img, &(img->bits_per_pixel),
		&(img->line_length), &(img->endian));
	all->minimap.img = mlx_new_image(all->mlx, all->map.w, all->map.h);
	all->minimap.addr = mlx_get_data_addr(
			all->minimap.img, &(all->minimap.bits_per_pixel),
			&(all->minimap.line_length), &(all->minimap.endian));
	map_gen(all);
	player_pos(all);
}
