#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <sys/time.h>
#include <pthread.h>
#include <stdbool.h>

typedef enum e_philo_is
{
	ALIVE,
	DEAD,
	FULL
}	t_philo_status;

typedef struct s_philo
{
	t_data			*data;
	t_fork			*forks;
	pthread_t		thread_philo;
	int				id;
	t_philo_status	status;
	pthread_mutex_t	mutex_status;
	int				nr_has_eaten;
	int				a;
}	t_philo;

bool	philo_alive(t_philo *philo)
{
	if (ft_strncmp(philo->status, ALIVE, 5))
		return (false);
	return (true);
}

bool	philosopher_is(char *action, t_philo *philo)
{
	if (ft_strncmp(action, "EATING", 6) == 0)
	{
		if (philo_has_taken_forks(philo))
		{
			set_philo_status(ALIVE, philo);
			my_sleep(philo->data->time_to_eat);
			philo->nr_has_eaten += 1;
			philo_dropped_forks(philo);
			return (true);
		}
		else
			return (false);
	}
	else if (ft_strncmp(action, "SLEEPING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is sleeping");
		my_sleep(philo->data->time_to_sleep);
		return (true);
	}
	else if (ft_strncmp(action, "THINKING", 8) == 0)
	{
		set_philo_status(ALIVE, philo);
		print_schedule(philo, "is thinking");
		return (true);
	}
	else
		return (false);
}
