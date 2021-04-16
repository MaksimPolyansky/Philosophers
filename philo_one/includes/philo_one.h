/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:40 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/16 19:23:13 by heusebio         ###   ########.fr       */
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

int					ft_strlen(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(char *str);
void				*died(void *data);
t_phils				**parse(int ac, char **av);
__uint64_t			my_time(void);
void				print_info(t_phils *phil, char *line);

void				*run(void *data);

#endif
