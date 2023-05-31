/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit_exec.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:44:28 by nmilan            #+#    #+#             */
/*   Updated: 2023/05/05 13:44:30 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/exec.h"
#include "../../includes/parsing.h"

int	free_exec_struct(t_player *p, t_data_game *data, char *str)
{
	if (p)
	{
		ft_free(p->position);
		if (p->rcast)
		{
			ft_free(p->rcast->hor);
			ft_free(p->rcast->ver);
			if (p->rcast->imgdata)
				mlx_destroy_image(data->mlx, p->rcast->imgdata->img);
			ft_free(p->rcast->imgdata);
			ft_free(p->rcast);
		}
		if (p->mlx_win)
			mlx_destroy_window(data->mlx, p->mlx_win);
		ft_free(p);
	}
	clean_data(*data, str);
	return (0);
}
