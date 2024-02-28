#include "philo.h"

void	thinking(t_philo *philo)
{
	write_message("is thinking", philo, philo->id);
}

void	sleeping(t_philo *philo)
{
	write_message("is sleeping", philo, philo->id);
	ft_usleep(philo->program->time_to_sleep);
}

void	eating(t_philo *philo)
{
	pthread_mutex_lock(philo->r_fork);
	write_message("has taken a fork", philo, philo->id);
	if (philo->program->num_of_philos == 1)
	{
	    ft_usleep(philo->program->time_to_die);
	    pthread_mutex_unlock(philo->r_fork);
	    return ;
	}
	pthread_mutex_lock(philo->l_fork);
	write_message("has taken a fork", philo, philo->id);
	//philo->eating = 1;
	write_message("is eating", philo, philo->id);
	pthread_mutex_lock(&philo->program->meal_mutex);
	philo->last_meal = current_time_m();
	philo->meals_eaten++;
	pthread_mutex_unlock(&philo->program->meal_mutex);
	ft_usleep(philo->program->time_to_eat);
	//philo->eating = 0;
	pthread_mutex_unlock(philo->l_fork);
	pthread_mutex_unlock(philo->r_fork);
}
