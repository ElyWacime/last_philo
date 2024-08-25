/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:48:05 by welyousf          #+#    #+#             */
/*   Updated: 2024/06/05 15:42:50 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	display_msg(t_philo *philo, char *msg)
{
	long	time;

	time = get_time() - philo->table->start_time;
	if (mutex_lock(&philo->table->dead_mutex))
		return (ft_error("Error locking the mutex dead!\n"));
	if (!philo->table->dead)
	{
		if (mutex_lock(&philo->table->print))
			return (ft_error("Error locking the mutex print!\n"));
		printf("%ld %ld %s\n", time, philo->id, msg);
		if (mutex_unlock(&philo->table->print))
			return (ft_error("Error unlocking the mutex print!\n"));
	}
	if (mutex_unlock(&philo->table->dead_mutex))
		return (ft_error("Error unlocking the mutex dead!\n"));
	return (0);
}

int	check_dead(t_table *table)
{
	mutex_lock(&table->dead_mutex);
	if (table->dead)
	{
		mutex_unlock(&table->dead_mutex);
		return (1);
	}
	mutex_unlock(&table->dead_mutex);
	return (0);
}

int	ft_error(char *str)
{
	write(2, str, ft_strlen(str));
	return (69);
}

int	init_mutex(t_table *table)
{
	long	i;

	i = -1;
	while (++i < table->philo_count)
	{
		if (pthread_mutex_init(&table->forks[i], NULL))
			return (ft_error("Mutex fork init failed!"));
	}
	if (pthread_mutex_init(&table->print, NULL))
		return (ft_error("Mutex print init failed!"));
	if (pthread_mutex_init(&table->dead_mutex, NULL))
		return (ft_error("Mutex dead init failed!"));
	return (0);
}

int	create_philos_forks(t_table *table)
{
	long	i;

	table->philos = malloc(sizeof(t_philo) * table->philo_count);
	table->forks = malloc(sizeof(pthread_mutex_t) * table->philo_count);
	if (!table->philos || !table->forks)
		return (ft_error("Malloc failed!"));
	if (init_mutex(table))
		return (1);
	i = -1;
	while (++i < table->philo_count)
	{
		table->philos[i].id = i + 1;
		table->philos[i].eat_count = 0;
		table->philos[i].table = table;
		table->philos[i].left_fork = (i + 1) % table->philo_count;
		table->philos[i].right_fork = i;
	}
	table->start_time = get_time();
	table->dead = 0;
	return (0);
}
