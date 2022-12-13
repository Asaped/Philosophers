#include "philosophers.h"

void	*routine(void *philo2)
{
	t_philo	*philo;

	philo = (t_philo *)philo2;
	philo->last_miam = timestamp();
	if (philo->pos % 2)
		usleep(15000);
	while (!is_dead(philo))
	{
		if (eat(philo) || philo->instance->stop)
			break ;
	}
	return (NULL);
}
