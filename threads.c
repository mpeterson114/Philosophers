#include "philo.h"

// static void	actions_loop(t_philo *philo)
// {
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->program->philo_die);
// 		if (philo->program->dead != 0)
// 		{
// 			pthread_mutex_unlock(&philo->program->philo_die);
// 			break ;
// 		}
// 		pthread_mutex_unlock(&philo->program->philo_die);
// 		eating(philo);
// 		if (philo->program->num_of_philos == 1
// 			|| philo->meals_eaten == philo->program->num_meals)
// 			break ;
// 		sleeping(philo);
// 		thinking(philo);
// 	}
// 	return ;
// }

// void	*monitor_routine(void *ph_pointer)
// {
// 	t_philo	*philo;
// 	int		meals_eaten;
// 	long	ph_die_time;

// 	philo = (t_philo *)ph_pointer;
// 	while (1)
// 	{
// 		pthread_mutex_lock(&philo->philo_lock);
// 		meals_eaten = philo->meals_eaten;
// 		ph_die_time = philo->ph_die_time;
// 		pthread_mutex_unlock(&philo->philo_lock);
// 		if (meals_eaten == philo->program->num_meals)
// 			break ;
// 		if (current_time_m() > ph_die_time)
// 		{
// 			write_msg("died", philo);
// 			return (NULL);
// 		}
// 	}
// 	return (NULL);
// }

// void	*philo_routine(void *ph_pointer)
// {
// 	t_philo	*philo;

// 	philo = (t_philo *) ph_pointer;
// 	philo->ph_die_time = philo->program->time_to_die + current_time_m();
// 	if (pthread_create(&philo->philo_monitor, NULL, &monitor_routine,
// 			(void *)philo))
// 		return ((void *)1);
// 	actions_loop(philo);
// 	if (pthread_join(philo->philo_monitor, NULL))
// 		return ((void *)1);
// 	return ((void *)0);
// }

int	create_threads(t_program *program)
{
	int			i;
    pthread_t   monitor;

    if(pthread_create(&monitor, NULL, &monitor_routine, program->philos))
        return (error("Monitor thread create error", program, 4));
	i = -1;
	// program->start_time = current_time_m();
	while (++i < program->num_of_philos)
	{
		if (pthread_create(&program->philos[i].thread, NULL, &philo_routine,
				&program->philos[i]))
			return (error("Philo thread create error", program, 4));
	}
	i = -1;
    if (pthread_join(monitor, NULL))
        return (error("Thread join error: monitor", program, 4));
	while (++i < program->num_of_philos)
	{
		if (pthread_join(program->philos[i].thread, NULL))
			return (error("Thread join error: ph_tid", program, 4));
	}
	return (0);
}