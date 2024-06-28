/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:56:28 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/28 19:22:33 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosopher.h"

static int	ft_atoi(const char *str)
{
	int		f;
	long	nbr;

	f = 1;
	nbr = 0;
	while ((*str >= 9 && *str <= 13) || *str == 32)
		str++;
	if (*str == '-' || *str == '+')
	{
		if (*str++ == '-')
			f *= -1;
	}
	while (*str >= '0' && *str <= '9')
		nbr = nbr * 10 + (*str++ - '0');
	if (nbr > INT32_MAX || (nbr == INT32_MAX && f == -1) || nbr < 0)
		return (0);
	return (nbr * f);
}

t_data	data_recolt(char *argv[])
{
	t_data	data;

	data.philo_nbr = ft_atoi(argv[1]);
	if (data.philo_nbr < 1 || data.philo_nbr > 200)
		return (printf("Error\nWrong Philosopher Input\n"), (t_data){0});
	data.lifespan = ft_atoi(argv[2]);
	if (data.lifespan <= 59)
		return (printf("Error\nStillborn Philosopher\n"), (t_data){0});
	data.eat_time = ft_atoi(argv[3]);
	if (data.eat_time < 60)
		return (printf(ERR_EAT), (t_data){0});
	data.sleep_time = ft_atoi(argv[4]);
	if (data.sleep_time <= 59)
		return (printf("Error\nThey need to sleep ya Bastard\n"), (t_data){0});
	if (argv[5])
	{
		data.eat_nbr = ft_atoi(argv[5]);
		if (data.eat_nbr <= 0)
			return (printf("Error\nThey need to eat ya Bastard\n"),
				(t_data){0});
	}
	else
		data.eat_nbr = -1;
	return (data);
}
