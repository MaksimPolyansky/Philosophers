/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_one.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/06 01:52:06 by heusebio          #+#    #+#             */
/*   Updated: 2021/02/14 14:28:48 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

typedef struct	s_phil
{
	char		*name;
	int			num_of_phil;
	int			time_to_die;
	int			time_to_eat;
	int			time_to_sleep;
	int			num_eat;
}				t_phil;

pthread_t t1;

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
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

void	*print(void *buf)
{
	for (size_t i = 0; i < 10; i++)
	{
		pthread_detach(t1);
		write(1, (char*)buf, strlen(buf));
		usleep(100000);
	}
	return NULL;
}

int		parse(t_phil *phil, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		phil->name = av[0];
		phil->num_of_phil = ft_atoi(av[1]);
		phil->time_to_die = ft_atoi(av[2]);
		phil->time_to_eat = ft_atoi(av[3]);
		phil->time_to_sleep = ft_atoi(av[4]);
		if (ac == 6)
			phil->num_eat = ft_atoi(av[5]);
		else
			phil->num_eat = 0;
		if (phil->num_of_phil < 2 || phil->num_of_phil > 200 || \
		phil->time_to_die < 60 || phil->time_to_eat < 60 || \
		phil->time_to_sleep < 60 || phil->num_eat < 0)
		{
			printf("Bad arguments!\n");
			return (EXIT_FAILURE);
		}
	}
	else
	{
		printf("Bad arguments!\nOnly 4 or 5 arguments!\n");
		return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}

int		main(int ac, char **av)
{
	t_phil	phil;
	char *str1 = "1_2_3_4_5_6_7_8_9\n";

	if (parse(&phil, ac, av))
		return (EXIT_FAILURE);
	pthread_create(&t1, NULL, print, (void*)str1);
	//pthread_join(t1, NULL);
	usleep(1000000);
	return (EXIT_SUCCESS);
}

//timestamp_in_ms X has taken a fork
//timestamp_in_ms X is eating
//timestamp_in_ms X is sleeping
//timestamp_in_ms X is thinking
//timestamp_in_ms X died
