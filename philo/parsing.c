/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:43:00 by welyousf          #+#    #+#             */
/*   Updated: 2024/05/31 12:30:38 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int check_str(char *str)
{
	int i;
	
	while (ft_is_space(*str))
		str++;
	if (*str == '+')
		str++;
	i = 0;
	while (ft_is_num(str[i]))
		i++;
    while (ft_is_space(str[i]))
    {
		i++;
	}
	return (i != ft_strlen(str) || ft_strlen(str) == 0);
}

int	parsing_input(int ac, char *av[])
{
	int i;

	if (!(ac == 6 || ac == 5))
		return (ft_error("Wrong number of arguments!"));
	i = 0;
	while (++i < ac)
	{
		if (check_str(av[i]))
			return (ft_error("Not a valid number!"));
	}
	return (0);	
}

int check_for_negative(t_table  *table)
{
    if (table->philo_count < 0
        || table->time_to_die < 0
        || table->time_to_eat < 0
        || table->time_to_sleep < 0
        || table->must_eat_count < 0)
        return (1);
    return (0);
}

int get_data(char **str, t_table *table)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	if (i  == 6)
		table->must_eat_count = ft_atoi(str[5]);
	else if (i == 5)
		table->must_eat_count = 9223372036854775807;
	table->philo_count = ft_atoi(str[1]);
	table->time_to_die = ft_atoi(str[2]);
	table->time_to_eat = ft_atoi(str[3]);
	table->time_to_sleep = ft_atoi(str[4]);
	if (check_for_negative(table))
        return (ft_error("Number too large!"));
    return (0);
}