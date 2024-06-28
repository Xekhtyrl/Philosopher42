/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/30 16:09:17 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/30 19:44:43 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../Includes/philosopher.h"

long	get_time(void)
{
	long			time;
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	time = tv.tv_sec * 1000 + tv.tv_usec / 1000;
	return (time);
}

void	ml_sleep(int ms)
{
	atomic_long	start;

	start = get_time();
	while (get_time() < start + ms)
		usleep(500);
}

void	print_status(atomic_long time, int id, char	*color, int status)
{
	if (status == 1)
		printf("%li\t%i\thas taken a fork\n", time, id);
	else if (status == 2)
		printf("%s%li\t%i\tis eating%s\n", color, time, id, NC);
	else if (status == 3)
		printf("%s%li\t%i\tis sleeping%s\n", color, time, id, NC);
	else if (status == 4)
		printf("%s%li\t%i\tis thinking%s\n", color, time, id, NC);
	else
		printf("%s%li\t%i\tdied%s\n", color, time, id, NC);
}
