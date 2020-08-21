/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cub3d.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vminomiy <vminomiy@students.42sp.org.br    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/11 06:29:15 by vminomiy          #+#    #+#             */
/*   Updated: 2020/08/21 09:37:50 by vminomiy         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int		g_error_number;

int					exit_game(t_all *all, int ret)
{
	free_map(all);
	free_file(all);
	exit(ret);
}

int					launch_game(t_all *all)
{
	ft_init(all);
	if (!(ft_init2(all)) || !(load_file(all, all->file.filename)))
	{
		printf("aqui");
		return (0);
	}
	window_init(all, &all->img, &all->map);
	return (1);
}

int					check_args(t_all *all, int argc, char **argv)
{
	if (argc <= 1)
		return (error_exit("ERROR\nNot enough arguments\nUSE: ./cub3d [mapfile.cub]"));
	else if (ft_strlen(argv[1]) <= 4 || ft_strncmp(argv[1] +
				(ft_strlen(argv[1]) - 4), ".cub", 4) != 0)
		return (error_exit("ERROR\nInvalid Map Name]"));
	if (argc == 3 && ft_strncmp(argv[2], "--save", 6) != 0)
		return (error_exit("ERROR\nInvalid second argument.\nUSE: --save"));
	if (g_error_number)
		return (0);
	all->file.filename = argv[1];
	return (argc -1);
}

int					main(int argc, char **argv)
{
	t_all			all;
	int				args;

	if (!(all.mlx = mlx_init()))
		return (error_exit("ERROR\nMLX could not start properly"));
	args = check_args(&all, argc, argv);
	if (!(args))
		hook_close(&all);
	if (!(launch_game(&all)))
		exit_game(&all, EXIT_SUCCESS);
	if (args == 2)
		exit_game(&all, EXIT_FAILURE);
	mlx_loop(all.mlx);
	return (0);
}