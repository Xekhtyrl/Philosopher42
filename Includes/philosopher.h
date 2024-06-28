/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosopher.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lvodak <lvodak@student.s19.be>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/16 15:20:45 by lvodak            #+#    #+#             */
/*   Updated: 2024/03/30 19:47:07 by lvodak           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHER_H
# define PHILOSOPHER_H

# include <stdio.h>
# include <stdlib.h>
# include <pthread.h>
# include <unistd.h>
# include <sys/time.h>
# include <stdatomic.h>
# include <string.h>

# define ERR_EAT "Error\nInvalid Eating Time (they can't eat that fast)\n"
# define GREEN "\033[0;32m\x1b[1m"
# define LBLUE "\033[0;36m\x1b[1m"
# define BLUE "\033[0;34m\x1b[1m"
# define RED "\033[0;31m\x1b[1m"
# define WHITE "\033[0;30m"
# define NC "\033[0m"

struct	s_philo;

//_______________STRUCTURES______________//
typedef struct s_data
{
	int				philo_nbr;
	int				lifespan;
	int				eat_time;
	int				sleep_time;
	int				eat_nbr;
	atomic_long		start_time;
	struct s_philo	*philo;
	atomic_int		end;
}	t_data;

typedef struct s_philo
{
	atomic_int		id;
	pthread_t		philo;
	atomic_long		last_dinner;
	atomic_int		is_eating;
	atomic_int		fork_lf;
	atomic_int		fork_used;
	pthread_mutex_t	fork;
	t_data			*data;
	atomic_int		alive;
	atomic_int		dinner;
}	t_philo;

//________________PARSING________________//
t_data	data_recolt(char *argv[]);
//________________ROUTINE________________//
void	*philo_routine(void	*param);
void	check_death(t_data *data);
//________________THREAD_________________//
int		thread_maker(t_data *data);
//_________________UTILS_________________//
long	get_time(void);
void	ml_sleep(int ms);
void	print_status(atomic_long time, int id, char	*color, int status);
//____________CLEAR_FUNCTIONNS___________//
int		end_condition(t_data *data, int i, long start, atomic_int count);
void	delete_all_mutex(t_data *data);

#endif