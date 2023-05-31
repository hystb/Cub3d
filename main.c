/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nmilan <nmilan@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/05/05 13:44:28 by nmilan            #+#    #+#             */
/*   Updated: 2023/05/05 13:44:30 by nmilan           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "includes/parsing.h"
#include "includes/exec.h"

int	main(int argc, char **argv)
{
	t_data_game	data;
	int i = -1;

	if (argc < 2)
		return (write(STDERR_FILENO, "Error\nNot in off args\n", 22));
	//peut-etre a enlever
	if (argc > 2)
		return (write(STDERR_FILENO, "Error\nToo much args\n", 20));
	//-------
	data = read_map(argv[1], 0, 0);
	pars_map(&data);
	while (data.map[++i])
		printf("%s", data.map[i]);
	do_render_loop(&data);
	clean_data(data, NULL);
	return (0);
}
