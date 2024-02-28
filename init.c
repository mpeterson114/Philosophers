#include "philo.h"

void	args_fill(t_program *program, char **argv, char argc)
{
	program->num_of_philos = ft_atoi(argv[1]);
	program->time_to_die = ft_atoi(argv[2]);
	program->time_to_eat = ft_atoi(argv[3]);
	program->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		program->num_meals = ft_atoi(argv[5]);
	else
		program->num_meals = -1;
}

void	init_philos(t_program *program)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		program->philos[i].id = i + 1;
        program->philos[i].eating = 0;
        program->philos[i].meals_eaten = 0;
        program->philos[i].last_meal = current_time_m();
        program->philos[i].start_time = current_time_m();
		program->philos[i].program = program;
		program->philos[i].l_fork = &program->forks[i];
        if (i == 0)
            program->philos[i].r_fork = &program->forks[program->num_of_philos - 1];
        else
            program->philos[i].r_fork = &program->forks[i - 1];
		i++;
	}
}

int	init_forks(t_program *program)
{
	int	i;

	i = -1;
	while (++i < program->num_of_philos)
	{
		if (pthread_mutex_init(&program->forks[i], NULL) != 0)
			return (error("Error initializing fork mutexes", program, 2));
	}
	return (0);
}

int	init_program(t_program *program, char **argv, char argc)
{
	args_fill(program, argv, argc);
	program->dead = 0;
    program->philos = malloc(sizeof(t_philo) * program->num_of_philos);
	if (!program->philos)
		return (error("Philos alloc error\n", program, 1));
	pthread_mutex_init(&program->meal_mutex, NULL);
	pthread_mutex_init(&program->message_mutex, NULL);
	pthread_mutex_init(&program->death_mutex, NULL);
	program->forks = malloc(sizeof(pthread_mutex_t) * program->num_of_philos);
	if (!program->forks)
	    return (error("Forks alloc error\n", program, 2));
	return (0);
}

int	start(t_program *program, char **argv, int argc)
{
	if (init_program(program, argv, argc) == 1)
		return (1);
	if (init_forks(program) == 1)
		return (1);
	init_philos(program);
	return (0);
}