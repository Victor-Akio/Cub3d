/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/29 23:24:25 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/29 23:42:19 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/cub3d.h"

int		get_tile(t_all *all, int x, int y)
{
	if (x < 0 || y < 0 || x > all->map.w - 1 || y > all->map.h - 1)
		return (0);
	return (all->map.map[y][x]);
}

void	circle(t_all *all, int r)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (i < all->map.h)
	{
		j = 0;
		while (j < all->map.w)
		{
			if ((pow(i - all->player.pos.x, 2) +
					(pow(j - all->player.pos.y, 2))) <= pow(r, 2))
				my_pixel_put(&(all->minimap), i, j, 0xC31433);
			j++;
		}
		i++;
	}
}

void	rotate_horizontal(double ang, t_dxy in, t_dxy *out)
{
	t_dxy		tmp;
	double		radian;

	radian = ang * (PI / 180);
	tmp.x = in.x;
	tmp.y = in.y;
	out->x = (cos(radian) * tmp.x) + (sin(radian) * tmp.y);
	out->y = (-sin(radian) * tmp.x) + (cos(radian) * tmp.y);
}

int		player_pos(t_all *all)
{
	if (all->player.pos.x <= 0 || all->player.pos.y <= 0)
	{
		error_exit("ERROR\nSomething went wrong with the player.");
		return (0);
	}
	if (all->player.way == 'N')
		rotate_horizontal(NV, all->player.dir, &all->player.dir);
	else if (all->player.way == 'S')
		rotate_horizontal(SV, all->player.dir, &all->player.dir);
	else if (all->player.way == 'w')
		rotate_horizontal(WV, all->player.dir, &all->player.dir);
	else if (all->player.way == 'E')
		rotate_horizontal(EV, all->player.dir, &all->player.dir);
	all->map.map[(int)all->player.map.x][(int)all->player.map.y] = '0';
	circle(all, 2);
	return (1);
}
