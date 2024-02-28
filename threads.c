#include "philo.h"

int	death_checker(t_philo *philo)
{
	pthread_mutex_lock(&philo->program->death_mutex);
	if (philo->program->dead != 0)
	{
		pthread_mutex_unlock(&philo->program->death_mutex);
		return (1);
	}
	pthread_mutex_unlock(&philo->program->death_mutex);
	return (0);
}

void	*philo_routine(void *ph_pointer)
{
	t_philo	*philo;

	philo = (t_philo *) ph_pointer;
	if (philo->id % 2 == 0)
		ft_usleep(1);
	while (!death_checker(philo))
	{
		eating(philo);
		sleeping(philo);
		thinking(philo);
	}
	return (ph_pointer);
}

int	create_threads(t_program *program)
{
	int			i;
    pthread_t   monitor;

    if(pthread_create(&monitor, NULL, &monitor_routine, program->philos))
        return (error("Monitor thread create error", program, 2));
	i = -1;
	// program->start_time = current_time_m();
	while (++i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]))
			return (error("Philo thread create error", program, 2));
	}
	i = -1;
    if (pthread_join(monitor, NULL))
        return (error("Thread join error: monitor", program, 2));
	while (++i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			return (error("Thread join error: ph_tid", program, 2));
	}
	return (0);
}