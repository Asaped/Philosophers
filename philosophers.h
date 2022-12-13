#ifndef PHILOSOPHERS_H
# define PHILOSOPHERS_H

# include <stdio.h>
# include <unistd.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>
# include <limits.h>
# include <stdbool.h>

typedef struct s_philo
{
	int				pos;
	int				l_fork;
	int				r_fork;
	int				miam_eated;
	int				is_eating;
	long int		last_miam;
	struct s_tab	*instance;
}					t_philo;

typedef struct s_tab
{
	long int		ttdie;
	long int		tteat;
	long int		ttsleep;
	long int		first_ts;
	int				nb_philo;
	int				nb_eat;
	int				stop;
	t_philo			*philo;
	pthread_mutex_t	*forks_mutex;
	pthread_mutex_t	print_mutex;
	pthread_mutex_t	death_mutex;
}				t_tab;

int			args_init(char **av, t_tab *info);
int			ft_log(int stop_code);
int			ft_atoi(char *str);
int			philo_init(t_tab *info);
int			mutex_init(t_tab *info);
int			start(t_tab *info);
long long	timestamp(void);
void		ft_msg(t_philo *philo, long int timestamp, int num);
void		*routine(void *philo);
int			eat(t_philo *philo);
int			is_dead(t_philo *philo);
void		ft_usleep(long int ms);
void		stop(t_tab *info, pthread_t *tid);
void		free_info(t_tab *info);

#endif
