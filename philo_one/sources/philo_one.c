/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philso_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:06 by heusebio          #+#    #+#             */
/*   Updated: 2021/02/14 14:28:48 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

pthread_mutex_t	mutex_g;

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int	ft_strcmp(const char *s1, const char *s2)
{
	unsigned char	*str1;
	unsigned char	*str2;
	size_t			i;

	str1 = (unsigned char *)s1;
	str2 = (unsigned char *)s2;
	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] != str2[i] || !str1[i])
			return (str1[i] - str2[i]);
		i++;
	}
	if (str1[i] || str2[i])
		return (str1[i] - str2[i]);
	return (0);
}

int		ft_atoi(char *str)
{
	int			i;
	long long	res;
	long long	neg;

	i = 0;
	res = 0;
	neg = 1;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\t'
	|| str[i] == '\f' || str[i] == ' ' || str[i] == '0')
		i++;
	if (str[i] == '-')
		neg = -1;
	if (str[i] == '-' || str[i] == '+')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
		res = (res * 10) + (str[i++] - '0');
	if (i >= 19)
	{
		if (neg == 1)
			return (-1);
		else if (i > 19)
			return (0);
	}
	return (res * neg);
}

void	my_zero(t_phils **phil, int ac, char **av)
{
	*(phil) = (t_phils*)malloc(sizeof(t_phils));
	if (*(phil) == NULL)
		exit(EXIT_FAILURE);
	(*phil)->num_of_phil = ft_atoi(av[1]);
	(*phil)->time_to_die = (__uint64_t)ft_atoi(av[2]);
	(*phil)->time_to_eat = ft_atoi(av[3]);
	(*phil)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*phil)->num_eat = ft_atoi(av[5]);
	else
		(*phil)->num_eat = 0;
	(*phil)->count_eat = 0;
	(*phil)->lfork = NULL;
	(*phil)->rfork = NULL;
}

t_phils	**parse(int ac, char **av)
{
	t_phils	**phils;
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200 || \
		ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || \
		ft_atoi(av[4]) < 60 || (ac == 6 && ft_atoi(av[5]) < 0))
			exit(EXIT_FAILURE);
		phils = (t_phils**)malloc(sizeof(t_phils*) * ft_atoi(av[1]));
		if (phils == NULL)
			exit(EXIT_FAILURE);
		i = -1;
		while (++i < ft_atoi(av[1]))
		{
			my_zero(&phils[i], ac, av);
			phils[i]->pos = i;
		}
	}
	else
		exit(EXIT_FAILURE);
	return (phils);
}

__uint64_t	my_time(void)
{
	struct timeval	_time;
	gettimeofday(&_time, NULL);
	return ((_time.tv_sec * (__uint64_t)1000) + (_time.tv_usec / 1000));
}

void	print_info(t_phils *phil, char *line)
{
	pthread_mutex_lock(phil->print_mutex);
	if (*phil->die == 1)
	{
		pthread_mutex_unlock(phil->print_mutex);
		return ;
	}
	printf("%lu %d %s\n", my_time() - phil->start_t, phil->pos + 1, line);
	pthread_mutex_unlock(phil->print_mutex);
}

void	*run(void *data)
{
	t_phils	*phil;

	phil = (t_phils*)data;
	phil->end_eat = my_time() - phil->start_t;
	if (phil->pos % 2)
		usleep(1000);
	while (1)
	{
		print_info(phil, "is thinking");
		pthread_mutex_lock(&phil->lfork->mutex_f);
		pthread_mutex_lock(&phil->rfork->mutex_f);
		print_info(phil, "has taken a forks");
		phil->lfork->fork = 0;
		phil->rfork->fork = 0;
		phil->end_eat = my_time() - phil->start_t;
		print_info(phil, "is eating");
		usleep(phil->time_to_eat * 1000);
		phil->lfork->fork = 1;
		phil->rfork->fork = 1;
		pthread_mutex_unlock(&phil->lfork->mutex_f);
		pthread_mutex_unlock(&phil->rfork->mutex_f);
		phil->count_eat++;
		if (phil->count_eat == phil->num_eat)
			(*phil->eat)++;
		print_info(phil, "is sleeping");
		usleep(phil->time_to_sleep * 1000);
	}
	return (NULL);
}

void	*died(void *data)
{
	t_phils	*phil;
	__uint64_t	_time;

	phil = (t_phils*)data;
	pthread_create(&phil->thread, NULL, run, phil);
	usleep(2000);
	while (1)
	{
		_time = my_time() - phil->start_t;
		if ((_time - phil->end_eat) > phil->time_to_die)
		{
			// printf("%lu - %lu = %lu > %lu\n", _time, phil->end_eat, _time - phil->end_eat, phil->time_to_die);
			print_info(phil, "died");
			*phil->die = 1;
			pthread_detach(phil->thread);
			return (NULL);
		}
		if (*phil->die || *phil->eat == phil->num_of_phil)
		{
			pthread_detach(phil->thread);
			return (NULL);
		}
	}
	return (NULL);
}

int		main(int ac, char **av)
{
	t_phils	**phils;
	int		i;
	int		p;
	int		k;
	int		z;
	int		*d;
	int		*w;
	__uint64_t	start;

	phils = parse(ac, av);
	i = 0;
	phils[i]->lfork = (t_fork*)malloc(sizeof(t_fork));
	if (phils[i]->lfork == NULL)
		exit(EXIT_FAILURE);
	phils[i]->lfork->fork = 1;
	pthread_mutex_init(&phils[i]->lfork->mutex_f, NULL);
	i = -1;
	while (++i < phils[0]->num_of_phil - 1)
	{
		phils[i]->rfork = (t_fork*)malloc(sizeof(t_fork));
		if (phils[i]->rfork == NULL)
			exit(EXIT_FAILURE);
		phils[i]->rfork->fork = 1;
		pthread_mutex_init(&phils[i]->rfork->mutex_f, NULL);
		phils[i + 1]->lfork = phils[i]->rfork;
	}
	phils[i]->rfork = phils[0]->lfork;

	d = (int*)malloc(sizeof(int));
	w = (int*)malloc(sizeof(int));
	if (d == 0 || w == 0)
		exit(EXIT_FAILURE);
	*d = 0;
	*w = 0;
	pthread_mutex_t		*mutex_t;
	mutex_t = malloc(sizeof(pthread_mutex_t));
	pthread_mutex_init(mutex_t, NULL);
	p = -1;
	start = my_time();
	while (++p < phils[0]->num_of_phil)
	{
		phils[p]->die = d;
		phils[p]->eat = w;
		phils[p]->print_mutex = mutex_t;
		phils[p]->start_t = start;
	}
	k = -1;
	while (++k < phils[0]->num_of_phil)
		pthread_create(&phils[k]->thread_d, NULL, died, phils[k]);

	z = -1;
	while (++z < phils[0]->num_of_phil)
	{
		pthread_join(phils[z]->thread_d, NULL);
	}
	return (EXIT_SUCCESS);
}
