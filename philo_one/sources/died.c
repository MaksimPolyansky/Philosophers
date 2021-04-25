/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   died.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:19:21 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/25 04:54:50 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_one.h"

int	g_tmp;

void	*died(void *data)
{
	t_phils		*phil;
	size_t		time;

	phil = (t_phils *)data;
	while (1)
	{
		time = my_time() - phil->start_t;
		if ((time - phil->end_eat) > phil->time_to_die)
		{
			*phil->die = 1;
			g_die = 1;
			!g_tmp && printf("%lu %d died\n", my_time() \
				- phil->start_t, phil->pos + 1);
			g_tmp = 1;
			return (NULL);
		}
		if (*phil->die || *phil->eat == phil->num_of_phil)
		{
			return (NULL);
		}
	}
	return (NULL);
}
