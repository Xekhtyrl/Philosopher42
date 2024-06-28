/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clear_functions.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/26 21:44:05 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/30 19:36:23 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosopher.h"

void	delete_all_mutex(t_data *data)
{
	int	i;

	i = -1;
	while (++i < data->philo_nbr)
		pthread_mutex_destroy(&data->philo[i].fork);
	return ;
}

int	end_condition(t_data *data, int i, long start, atomic_int count)
{
	int	x;

	x = -1;
	if (data->philo[i].dinner < data->eat_nbr || data->eat_nbr == -1)
	{
		if (data->philo[i].last_dinner > data->start_time
			&& start - data->philo[i].last_dinner > data->lifespan
			&& !data->philo[i].is_eating)
		{
			data->philo[i].alive = 0;
			data->end = data->philo_nbr;
			print_status(start - data->start_time, data->philo[i].id, RED, 5);
			while (++x < data->philo_nbr)
				data->philo[x].alive = 0;
			return (data->philo_nbr);
		}
	}
	return (count);
}
