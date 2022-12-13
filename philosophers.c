#include "philosophers.h"

int	is_dead(t_philo *philo)
{
	pthread_mutex_lock(&philo->instance->death_mutex);
	if (timestamp() - philo->last_miam > philo->instance->ttdie)
	{	
		ft_msg(philo, timestamp() - philo->instance->first_ts, 2);
		philo->instance->stop = 1;
		pthread_mutex_unlock(&philo->instance->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->instance->death_mutex);
	return (0);
}

void	free_info(t_tab *info)
{
	free(info->philo);
	free(info->forks_mutex);
}

void	stop(t_tab *info, pthread_t *tid)
{
	int	i;

	i = -1;
	while (++i < info->nb_philo)
		pthread_join(tid[i], NULL);
	free(tid);
	i = -1;
	while (++i < info->nb_philo)
		pthread_mutex_destroy(&(info->forks_mutex[i]));
	pthread_mutex_destroy(&(info->print_mutex));
	pthread_mutex_destroy(&(info->death_mutex));
	free_info(info);
}

int	eat(t_philo *philo)
{
	pthread_mutex_lock(&philo->instance->forks_mutex[philo->l_fork]);
	ft_msg(philo, timestamp() - philo->instance->first_ts, 1);
	pthread_mutex_lock(&philo->instance->forks_mutex[philo->r_fork]);
	ft_msg(philo, timestamp() - philo->instance->first_ts, 1);
	pthread_mutex_lock(&philo->instance->death_mutex);
	philo->last_miam = timestamp();
	ft_msg(philo, timestamp() - philo->instance->first_ts, 3);
	pthread_mutex_unlock(&philo->instance->death_mutex);
	ft_usleep(philo->instance->tteat);
	philo->miam_eated += 1;
	pthread_mutex_unlock(&philo->instance->forks_mutex[philo->l_fork]);
	pthread_mutex_unlock(&philo->instance->forks_mutex[philo->r_fork]);
	if (philo->miam_eated == philo->instance->nb_eat
		&& philo->instance->nb_eat != -1)
	{
		ft_msg(philo, timestamp() - philo->instance->first_ts, 6);
		return (1);
	}
	ft_msg(philo, timestamp() - philo->instance->first_ts, 4);
	ft_usleep(philo->instance->ttsleep);
	ft_msg(philo, timestamp() - philo->instance->first_ts, 5);
	return (0);
}

int	start(t_tab *info)
{
	pthread_t	*tid;	
	int			i;

	i = 0;
	tid = malloc(sizeof(pthread_t) * info->nb_philo);
	if (!tid)
		return (1);
	info->first_ts = timestamp();
	while (i < info->nb_philo)
	{
		if (pthread_create(&tid[i], NULL, &routine, &info->philo[i]))
			return (1);
		i++;
	}
	stop(info, tid);
	return (0);
}
