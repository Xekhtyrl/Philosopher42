/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routine.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/21 18:00:29 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/30 21:10:04 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosopher.h"

static atomic_long	let_them_sleep(t_philo *philo)
{
	atomic_long	start;

	start = get_time();
	if (philo->data->end == philo->data->philo_nbr)
		return (0);
	print_status(start - philo->data->start_time, philo->id, BLUE, 3);
	ml_sleep(philo->data->sleep_time);
	return (get_time());
}

static atomic_long	pick_forks(t_philo *philo, t_data *data)
{
	if (data->end == data->philo_nbr)
		return (0);
	if (philo->id % 2)
	{
		pthread_mutex_lock(&philo->fork);
		print_status(get_time() - data->start_time, philo->id, WHITE, 1);
		if (data->end == data->philo_nbr)
			return (pthread_mutex_unlock(&philo->fork), 0);
		philo->fork_used = 1;
		pthread_mutex_lock(&data->philo[philo->fork_lf].fork);
		if (philo->alive && !data->end)
			print_status(get_time() - data->start_time, philo->id, WHITE, 1);
	}
	else
	{
		pthread_mutex_lock(&data->philo[philo->fork_lf].fork);
		print_status(get_time() - data->start_time, philo->id, WHITE, 1);
		if (data->end == data->philo_nbr)
			return (pthread_mutex_unlock(&data->philo[philo->fork_lf].fork), 0);
		philo->fork_used = 1;
		pthread_mutex_lock(&philo->fork);
		if (philo->alive && !data->end)
			print_status(get_time() - data->start_time, philo->id, WHITE, 1);
	}
	return (get_time());
}

static int	let_them_eat(t_philo *philo, t_data *data)
{
	atomic_long	start;

	if (data->end == data->philo_nbr)
		return (0);
	start = pick_forks(philo, data);
	if (!start || data->end == data->philo_nbr)
		return (0);
	philo->last_dinner = get_time();
	philo->is_eating = 1;
	print_status(get_time() - data->start_time, philo->id, GREEN, 2);
	philo->dinner++;
	ml_sleep(data->eat_time);
	pthread_mutex_unlock(&philo->fork);
	pthread_mutex_unlock(&(data->philo[philo->fork_lf].fork));
	philo->is_eating = 0;
	philo->fork_used = 0;
	start = let_them_sleep(philo);
	if (!start || data->end == data->philo_nbr)
		return (0);
	print_status(get_time() - data->start_time, philo->id, LBLUE, 4);
	return (1);
}

void	check_death(t_data *data)
{
	int				i;
	atomic_long		start;
	atomic_int		count;

	count = 0;
	while (1)
	{
		i = -1;
		ml_sleep(5);
		while (++i < data->philo_nbr)
		{
			start = get_time();
			count = end_condition(data, i, start, count);
			if ((count == data->philo_nbr || data->end == data->philo_nbr))
				return (delete_all_mutex(data));
		}
	}
}

void	*philo_routine(void	*param)
{
	t_philo	*philo;

	philo = param;
	philo->philo = pthread_self();
	pthread_mutex_init(&philo->fork, NULL);
	while (!philo->data->start_time)
		ml_sleep(1);
	philo->last_dinner = get_time();
	if ((philo->id % 2))
		ml_sleep(5);
	while (philo->alive && (philo->dinner < philo->data->eat_nbr
			|| philo->data->eat_nbr == -1))
	{
		if (philo->data->end < philo->data->philo_nbr)
		{
			if (!let_them_eat(philo, philo->data))
				break ;
		}
		else
			break ;
		if (philo->dinner == philo->data->eat_nbr)
			philo->data->end++;
	}
	return (NULL);
}
