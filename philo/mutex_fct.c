/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mutex_fct.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 14:28:58 by welyousf          #+#    #+#             */
/*   Updated: 2024/06/05 13:18:05 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

int pick_up_forks(t_philo *philo)
{
    if (mutex_lock(&philo->table->forks[philo->left_fork]))
        return (ft_error("Error locking the mutex left fork!\n"));
    display_msg(philo, "has taken a fork");
    if (mutex_lock(&philo->table->forks[philo->right_fork]))
        return (ft_error("Error locking the mutex right fork!\n"));
    display_msg(philo, "has taken a fork");
    return (0);
}

int pick_up_forks_(t_philo *philo)
{
    if (mutex_lock(&philo->table->forks[philo->right_fork]))
        return (ft_error("Error locking the mutex left fork!\n"));
    display_msg(philo, "has taken a fork");
    if (mutex_lock(&philo->table->forks[philo->left_fork]))
        return (ft_error("Error locking the mutex right fork!\n"));
    display_msg(philo, "has taken a fork");
    return (0);
}

int put_down_forks(t_philo *philo)
{
    if (mutex_unlock(&philo->table->forks[philo->left_fork]))
        return (ft_error("Error unlocking the mutex left fork!\n"));
    if (mutex_unlock(&philo->table->forks[philo->right_fork]))
        return (ft_error("Error unlocking the mutex right fork!\n"));
    return (0);
}

int put_down_forks_(t_philo *philo)
{
    if (mutex_unlock(&philo->table->forks[philo->right_fork]))
        return (ft_error("Error unlocking the mutex right fork!\n"));
    if (mutex_unlock(&philo->table->forks[philo->left_fork]))
        return (ft_error("Error unlocking the mutex left fork!\n"));
    return (0);
}

int mutex_lock(pthread_mutex_t *fork)
{
    if (pthread_mutex_lock(fork))
        return (ft_error("Error locking the mutex!\n"));
    return (0);
}

int mutex_unlock(pthread_mutex_t *fork)
{
    if (pthread_mutex_unlock(fork))
        return (ft_error("Error unlocking the mutex!\n"));
    return (0);
}
