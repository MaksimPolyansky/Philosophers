/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:40 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/15 21:40:02 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_ONE_H
# define PHILO_ONE_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>

typedef struct		s_fork
{
	int				fork;
	pthread_mutex_t	mutex_f;
}					t_fork;


typedef struct		s_phils
{
	int				pos;
	int				num_of_phil;
	__uint64_t		time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				count_eat;
	int				*die;
	int				*eat;
	__uint64_t		start_t;
	__uint64_t		end_eat;
	pthread_t		thread;
	pthread_t		thread_d;
	pthread_mutex_t	*print_mutex;
	t_fork			*lfork;
	t_fork			*rfork;
}					t_phils;


#endif
