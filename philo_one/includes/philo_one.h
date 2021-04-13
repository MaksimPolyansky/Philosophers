/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:40 by heusebio          #+#    #+#             */
/*   Updated: 2021/02/12 19:15:12 by heusebio         ###   ########.fr       */
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

typedef struct		s_phil
{
	int				pos;
	int				lfork;
	int				rfork;
	int				without_eat;
	pthread_mutex_t	lf;
	pthread_mutex_t	rf;
}					t_phil;


typedef struct		s_phils
{
	int				num_of_phil;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				lfork;
	int				rfork;
	t_phil			*phil;
	pthread_mutex_t	lf;
	pthread_mutex_t	rf;
	pthread_t		f;
}					t_phils;


#endif
