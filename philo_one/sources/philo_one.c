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

int		my_error(t_phils *phils, char *line)
{
	if (phils->phil != NULL)
		;
	printf("%s", line);
	exit(EXIT_FAILURE);
}

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

void	my_zero(t_phils *phils)
{
	phils->num_of_phil = 0;
	phils->time_to_die = 0;
	phils->time_to_eat = 0;
	phils->time_to_sleep = 0;
	phils->num_eat = 0;
	phils->phil = NULL;
}

void	parse(t_phils *phils, int ac, char **av)
{
	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200 || \
		ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || \
		ft_atoi(av[4]) < 60 || (ac == 6 && ft_atoi(av[5]) < 0))
			my_error(phils, "Bad arguments!\n");
		phils->num_of_phil = ft_atoi(av[1]);
		phils->time_to_die = ft_atoi(av[2]) * 1000;
		phils->time_to_eat = ft_atoi(av[3]) * 1000;
		phils->time_to_sleep = ft_atoi(av[4]) * 1000;
		if (ac == 6)
			phils->num_eat = ft_atoi(av[5]);
	}
	else
		my_error(phils, "Bad arguments!\nOnly 4 or 5 arguments!\n");
	if (!(phils->phil = (t_phil*)malloc(sizeof(t_phil) * phils->num_of_phil)))
		my_error(phils, "Bad malloc!");
}



int		main(int ac, char **av)
{
	t_phils	phils;

	my_zero(&phils);
	parse(&phils, ac, av);

	return (EXIT_SUCCESS);
}

/*
** timestamp_in_ms X has taken a fork
** timestamp_in_ms X is eating
** timestamp_in_ms X is sleeping
** timestamp_in_ms X is thinking
** timestamp_in_ms X died
*/
