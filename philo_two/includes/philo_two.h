/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:40 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/15 23:34:25 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <string.h>
# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <pthread.h>
# include <sys/time.h>
# include <semaphore.h>
# include <fcntl.h>

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
	sem_t			*print_sem;
	sem_t			*forks;
}					t_phils;

int					ft_strlen(char *str);
int					ft_strcmp(const char *s1, const char *s2);
int					ft_atoi(char *str);
t_phils				**parse(int ac, char **av);
void				*died(void *data);
void				*run(void *data);
void				print_info(t_phils *phil, char *line);
__uint64_t			my_time(void);

#endif
