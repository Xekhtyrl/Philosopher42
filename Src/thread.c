/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   thread.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 17:51:54 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/30 19:47:07 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosopher.h"

static void	philo_init(t_philo *philo, t_data *data, int i)
{
	philo->id = i + 1;
	if (i == 0)
		philo->fork_lf = data->philo_nbr - 1;
	else
		philo->fork_lf = i - 1;
	philo->fork_used = 0;
	philo->alive = 1;
	philo->data = data;
	philo->dinner = 0;
	philo->is_eating = 0;
}

int	thread_maker(t_data *data)
{
	int	i;

	data->philo = malloc(sizeof(t_philo) * data->philo_nbr);
	data->start_time = 0;
	i = -1;
	while (++i < data->philo_nbr)
	{
		philo_init(&data->philo[i], data, i);
		if (i == data->philo_nbr - 1)
			data->start_time = get_time();
		if (pthread_create(&(data->philo[i].philo), NULL, philo_routine,
				&data->philo[i]) < 0)
			return (/*free_thread(data, i)*/ printf("Error\nThread not created\n"), -1);
	}
	i = -1;
	check_death(data);
	while (++i < data->philo_nbr)
		pthread_join(data->philo[i].philo, NULL);
	return (0);
}
