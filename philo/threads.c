/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   threads.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:12:12 by welyousf          #+#    #+#             */
/*   Updated: 2024/08/25 22:18:37 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

static int	has_all_philo_eaten(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philo_count)
	{
		if (table->philos[i].eat_count < table->must_eat_count)
			return (0);
	}
	return (1);
}

static int	main_thread(t_table *table)
{
	long	i;

	while (1)
	{
		i = -1;
		while (table->philos[++i].id < table->philo_count)
		{
			mutex_lock(&table->dead_mutex);
			if (has_all_philo_eaten(table))
				table->dead = 2;
			if (get_time() - table->philos[i].last_meal > table->time_to_die)
			{
				table->dead += 1;
				if (table->dead == 1)
					printf("%ld %ld died\n", get_time() - table->start_time,
						table->philos[i].id);
				mutex_unlock(&table->dead_mutex);
				return (1);
			}
			mutex_unlock(&table->dead_mutex);
		}
	}
	return (0);
}

static void	*routine(void *ptr)
{
	t_philo	*philo;

	philo = (t_philo *)ptr;
	if (philo->id % 2)
	{
		display_msg(philo, "is sleeping");
		my_usleep(philo->table->time_to_sleep, philo);
	}
	while (!check_dead(philo->table))
	{
		display_msg(philo, "is thinking");
		pick_up_forks(philo);
		display_msg(philo, "is eating");
		mutex_lock(&philo->table->dead_mutex);
		philo->last_meal = get_time();
		philo->eat_count++;
		mutex_unlock(&philo->table->dead_mutex);
		if (my_usleep(philo->table->time_to_eat, philo))
			return (NULL);
		display_msg(philo, "is sleeping");
		put_down_forks(philo);
		if (my_usleep(philo->table->time_to_sleep, philo))
			return (NULL);
	}
	return (NULL);
}

int	start_threads(t_table *table)
{
	long	i;

	i = -1;
	table->start_time = get_time();
	while (++i < table->philo_count)
	{
		table->philos[i].last_meal = get_time();
		if (pthread_create(&table->philos[i].thread, NULL, &routine,
				&table->philos[i]))
			return (ft_error("Thread creation failed!"));
	}
	main_thread(table);
	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_join(table->philos[i].thread, NULL))
			return (ft_error("Thread join failed!"));
	}
	return (0);
}
