#include "philo.h"

void	write_message(char *str, t_philo *philo, int id)
{
	long time;

	pthread_mutex_lock(&philo->program->message_mutex);
	time = current_time_m() - philo->start_time;
	if (!death_checker(philo))
		printf("%zu %d %s\n", time, id, str);
	pthread_mutex_unlock(&philo->program->message_mutex);
}

static int past_time_limit(t_philo *philo, int time_to_die)
{
	pthread_mutex_lock(&philo->program->meal_mutex);
	if (current_time_m() - philo->last_meal >= time_to_die) //&&philo_eating?
	{
		pthread_mutex_unlock(&philo->program->meal_mutex);
		return (1);
	}  
	pthread_mutex_unlock(&philo->program->meal_mutex);
	return (0);
}

int	time_checker(t_philo *philo)
{
	int i;

	i = 0;
	while (i < philo->program->num_of_philos)
	{
		if (past_time_limit(&philo[i], philo->program->time_to_die))
		{
			write_message("died", &philo[i], &philo[i].id);
			pthread_mutex_lock(&philo->program->death_mutex);
			philo->program->dead = 1;
			pthread_mutex_unlock(&philo->program->death_mutex);
			return (1);
		}
		i++;
	}
	return (0);
}

int	meal_checker(t_philo *philo)
{
	int i;
	int done_eating;

	i = 0;
	done_eating = 0;
	if (philo->program->num_meals == -1)
		return (0);
	while (i < philo->program->num_of_philos)
	{
		pthread_mutex_lock(&philo->program->meal_mutex);
		if (philo[i].meals_eaten >= philo->program->num_meals)  // or == ??
			done_eating++;
		pthread_mutex_unlock(&philo->program->meal_mutex);
		i++;
	}
	if (done_eating == philo->program->num_of_philos)
	{
		pthread_mutex_lock(&philo->program->death_mutex);
		philo->program->dead = 1;
		pthread_mutex_unlock(&philo->program->death_mutex);
		return (1);
	}
	return (0);
}

void *monitor_routine(void *ph_pointer)
{
    t_philo *philos;

    philos = (t_philo *)ph_pointer;
    while (1)
	{
		if (time_checker(philos) || meal_checker(philos))
            break ;
	}
    return (ph_pointer);
}