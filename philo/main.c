/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:37:26 by welyousf          #+#    #+#             */
/*   Updated: 2024/08/22 15:41:38 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int	one_philo(t_table *table)
{
	if (table->philo_count == 1)
	{
		table->start_time = get_time();
		display_msg(&table->philos[0], "is thinking");
		display_msg(&table->philos[0], "has taken a fork");
		usleep(table->time_to_die * 1000);
		display_msg(&table->philos[0], "died");
		return (1);
	}
	return (0);
}

int	main(int ac, char *av[])
{
	t_table	table;

	(void)table;
	if (parsing_input(ac, av))
		return (1);
	if (get_data(av, &table))
		return (2);
	if (create_philos_forks(&table))
		return (3);
	if (one_philo(&table))
		return (4);
	if (start_threads(&table))
		return (5);
}
