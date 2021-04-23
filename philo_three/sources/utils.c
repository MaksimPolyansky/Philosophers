/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: heusebio <heusebio@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/04/15 23:26:10 by heusebio          #+#    #+#             */
/*   Updated: 2021/04/22 20:13:28 by heusebio         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/philo_three.h"

size_t	my_time(void)
{
	struct timeval	time;

	gettimeofday(&time, NULL);
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int		ft_strlen(char *str)
{
	int	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

int		ft_strcmp(const char *s1, const char *s2)
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
	int			p;
	long long	res;

	i = 0;
	p = 0;
	res = 0;
	while (str[i] == '\n' || str[i] == '\r' || str[i] == '\v' || str[i] == '\t'
		|| str[i] == '\f' || str[i] == ' ')
		i++;
	while ((str[i] >= '0') && (str[i] <= '9'))
	{
		p = 1;
		res = (res * 10) + (str[i++] - '0');
	}
	if (p == 0)
		return (-1);
	return (res);
}

void	print_info(t_phils *phil, char *line)
{
	sem_wait(phil->print_sem);
	if (phil->die == 1)
	{
		printf("%lu %d %s\n", my_time() - phil->start_t, phil->pos + 1, line);
		return ;
	}
	printf("%lu %d %s\n", my_time() - phil->start_t, phil->pos + 1, line);
	sem_post(phil->print_sem);
}
