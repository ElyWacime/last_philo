/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   time_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:54:44 by welyousf          #+#    #+#             */
/*   Updated: 2024/08/25 22:18:50 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	my_usleep(long duration, t_philo *philo)
{
	long	start;
	long	current;

	(void)philo;
	start = get_time();
	while (1)
	{
		current = get_time();
		if (current - start >= duration)
			break ;
		if (current - philo->last_meal > philo->table->time_to_die)
		{
			mutex_lock(&philo->table->dead_mutex);
			philo->table->dead += 1;
			if (philo->table->dead == 1)
				printf("%ld %ld died\n", get_time() - philo->table->start_time,
					philo->id);
			mutex_unlock(&philo->table->dead_mutex);
			return (1);
		}
		usleep(200);
	}
	return (0);
}

long	get_time(void)
{
	struct timeval	now;
	long			now_;

	if (gettimeofday(&now, NULL) == -1)
		return (ft_error("Error getting the time!"));
	now_ = (now.tv_sec * 1000L) + (now.tv_usec / 1000L);
	return (now_);
}
