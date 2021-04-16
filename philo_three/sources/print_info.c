/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_info.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:33:03 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/16 22:30:37 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

void	print_info(t_phils *phil, char *line)
{
	sem_wait(phil->print_sem);
	if (*phil->die == 1)
	{
		sem_post(phil->print_sem);
		return ;
	}
	printf("%lu %d %s\n", my_time() - phil->start_t, phil->pos + 1, line);
	sem_post(phil->print_sem);
}
