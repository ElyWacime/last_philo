/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: welyousf <welyousf@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/31 11:37:43 by welyousf          #+#    #+#             */
/*   Updated: 2024/06/05 13:18:53 by welyousf         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include <pthread.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/time.h>

typedef struct s_table	t_table;

typedef struct s_philo
{
    pthread_t		thread;
    long			id;
    long			left_fork;
    long			right_fork;
    long			eat_count;
    long			last_meal;
    t_table			*table;
}				t_philo;

typedef struct s_table
{
    long			philo_count;
    long			time_to_die;
    long			time_to_eat;
    long			time_to_sleep;
    long			must_eat_count;
    long			philo_full;
    long			start_time;
    long            dead;
    pthread_mutex_t dead_mutex;
    pthread_mutex_t	*forks;
    pthread_mutex_t	print;
    t_philo			*philos;
}				t_table;

/*
** prsing.c
*/
int check_str(char *str);
int	parsing_input(int ac, char *av[]);
int check_for_negative(t_table  *table);
int get_data(char **str, t_table *table);

/*
** helper_fct.c
*/
int	ft_is_num(char c);
int	ft_is_space(char c);
int ft_strlen(char *str);
int ft_error(char *str);
long ft_atoi(const char *str);

/*
** mutex_fct.c
*/
int mutex_lock(pthread_mutex_t *fork);
int mutex_unlock(pthread_mutex_t *fork);
int pick_up_forks(t_philo *philo);
int put_down_forks(t_philo *philo);
int pick_up_forks_(t_philo *philo);
int put_down_forks_(t_philo *philo);

/*
** utils.c
*/
int check_dead(t_table  *table);
int ft_error(char *str);
int create_philos_forks(t_table *table);
int display_msg(t_philo *philo, char *msg);

/*
** time_utils.c
*/
int    my_usleep(long duration, t_philo *philo);
long	get_time(void);

/*
** threads.c
*/
int start_threads(t_table *table);