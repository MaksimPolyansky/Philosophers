/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:21:52 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/18 05:16:37 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

void	my_zero(t_phils **phil, int ac, char **av)
{
	*(phil) = (t_phils *)malloc(sizeof(t_phils));
	if (*(phil) == NULL)
		exit(EXIT_FAILURE);
	(*phil)->num_of_phil = ft_atoi(av[1]);
	(*phil)->time_to_die = (size_t)ft_atoi(av[2]);
	(*phil)->time_to_eat = ft_atoi(av[3]);
	(*phil)->time_to_sleep = ft_atoi(av[4]);
	if (ac == 6)
		(*phil)->num_eat = ft_atoi(av[5]);
	else
		(*phil)->num_eat = 0;
	(*phil)->count_eat = 0;
	(*phil)->lfork = NULL;
	(*phil)->rfork = NULL;
	(*phil)->print_mutex = NULL;
	(*phil)->die = NULL;
	(*phil)->eat = NULL;
}

int	parse(t_phils ***phils, int ac, char **av)
{
	int		i;

	if (ac == 5 || ac == 6)
	{
		if (ft_atoi(av[1]) < 2 || ft_atoi(av[1]) > 200 || \
		ft_atoi(av[2]) < 60 || ft_atoi(av[3]) < 60 || \
		ft_atoi(av[4]) < 60 || (ac == 6 && ft_atoi(av[5]) < 0))
			return ((int)error_arg("Bad arguments!"));
		(*phils) = (t_phils **)malloc(sizeof(t_phils *) * ft_atoi(av[1]));
		if (phils == NULL)
			return ((int)error_arg("Bad malloc!"));
		i = -1;
		while (++i < ft_atoi(av[1]))
		{
			my_zero(&(*phils)[i], ac, av);
			(*phils)[i]->pos = i;
		}
	}
	else
		return ((int)error_arg("Bad arguments!"));
	return (1);
}
