/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:40 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 06:45:42 by heusebio         ###   ########.fr       */
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

typedef struct s_fork
{
	int				fork;
	pthread_mutex_t	mutex_f;
}					t_fork;

typedef struct s_phils
{
	int				pos;
	int				num_of_phil;
	size_t			time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				num_eat;
	int				count_eat;
	int				*die;
	int				*eat;
	size_t			start_t;
	size_t			end_eat;
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
int					parse(t_phils ***phils, int ac, char **av);
size_t				my_time(void);
void				print_info(t_phils *phil, char *line);
void				*error_arg(char *line);
void				*my_errors(t_phils ***phils, char *line);
int					init_mutex(t_phils ***phils, t_fork **fork_s);
int					init_forks(t_phils ***phils);
int					init_print(t_phils ***phils);
int					to_go(t_phils ***phils);
void				*run(void *data);

#endif
