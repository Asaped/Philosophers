#include "philosophers.h"

int	main(int ac, char **av)
{
	t_tab	info;

	if (ac != 5 && ac != 6)
		return (ft_log(2));
	if (args_init(av, &info))
		return (ft_log(1));
	if (philo_init(&info) || mutex_init(&info) || start(&info))
	{
		free_info(&info);
		return (ft_log(3));
	}
}
