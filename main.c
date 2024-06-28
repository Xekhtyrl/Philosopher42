/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:40:44 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/30 21:06:22 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "./Includes/philosopher.h"

int	main(int argc, char *argv[])
{
	t_data	data;

	if (argc < 5 || argc > 6)
		return (printf("Error\nWrong number of arguments\n"), -1);
	data = data_recolt(argv);
	if (data.philo_nbr == 1)
		return (printf("%s%i\t%i\tdied%s\n", RED, 0, 1, NC), 0);
	data.end = 0;
	if (data.lifespan == 0)
		return (0);
	thread_maker(&data);
	return (free(data.philo), 0);
}
