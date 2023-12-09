/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: moturki <marvin@42lausanne.ch>             +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/09 19:34:35 by moturki           #+#    #+#             */
/*   Updated: 2023/12/09 19:34:36 by moturki          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	ft_msg(t_philo *philo, long int timestamp, int num)
{
	pthread_mutex_lock(&philo->instance->print_mutex);
	if (!philo->instance->stop)
	{
		if (num == 1)
			printf("%lu %d has taken a fork\n", timestamp, philo->pos);
		else if (num == 2)
			printf("%lu %d died\n", timestamp, philo->pos);
		else if (num == 3)
			printf("%lu %d is eating\n", timestamp, philo->pos);
		else if (num == 4)
			printf("%lu %d is sleeping\n", timestamp, philo->pos);
		else if (num == 5)
			printf("%lu %d is thinking\n", timestamp, philo->pos);
		else if (num == 6)
			printf("%lu %d had finished his meals\n", timestamp, philo->pos);
	}
	pthread_mutex_unlock(&philo->instance->print_mutex);
}

long long	timestamp(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return (tv.tv_sec * 1000 + tv.tv_usec / 1000);
}

int	ft_atoi(char *str)
{
	int	neg;
	int	res;

	neg = 1;
	res = 0;
	while (*str == ' ' || (*str >= 9 && *str <= 13))
		++str;
	if (*str == '-')
		neg = -1;
	while (*str == '-' || *str == '+')
		++str;
	while (*str >= '0' && *str <= '9')
	{
		res = res * 10 + *str - '0';
		++str;
	}
	return (res * neg);
}

int	ft_log(int stop_code)
{
	if (stop_code == 1)
		write(2, "Erreur : Les paramètres entree sont incorrect.\n", 48);
	else if (stop_code == 2)
		write(2, "Erreur : Le nombre de parametres entree est incorrect.\n", 55);
	else if (stop_code == 3)
		write(2, "Erreur : Malloc\n", 16);
	return (1);
}

void	ft_usleep(long int ms)
{
	long int	t;

	t = timestamp();
	while (1)
	{
		if (timestamp() - t >= ms)
			break ;
		usleep(50);
	}
}
