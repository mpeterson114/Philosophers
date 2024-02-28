#include "philo.h"

void	free_program(t_program *program, int release)
{
	if (program->philos && release > 0)
		free(program->philos);
	if (program->forks && release > 1)
		free(program->forks);
}

void	exit_program(t_program *program, int release)
{
	int	i;

	i = 0;
	while (i < program->num_of_philos)
	{
		if (program->philos)
		{
			pthread_mutex_destroy(&program->philos[i].r_fork);
			pthread_mutex_destroy(&program->philos[i].l_fork);
		}
		if (program->forks)
			pthread_mutex_destroy(&program->forks[i]);
		i++;
	}
	pthread_mutex_destroy(&program->message_mutex);
	pthread_mutex_destroy(&program->meal_mutex);
	pthread_mutex_destroy(&program->death_mutex);
	free_program(program, release);
}

int	error(char *str, t_program *program, int release)
{
	printf("%s\n", str);
	if (program)
		exit_program(program, release);
	return (1);
}

int	check_args_input(char **argv)
{
	if (is_alpha_string(argv[1]) || ft_atoi(argv[1]) <= 0)
		return (error("Invalid number of philosophers", NULL, 0));
	if (is_alpha_string(argv[2]) || ft_atoi(argv[2]) <= 0)
		return (error("'time_to_die' invalid", NULL, 0));
	if (is_alpha_string(argv[3]) || ft_atoi(argv[3]) <= 0)
		return (error("'time_to_eat' invalid", NULL, 0));
	if (is_alpha_string(argv[4]) || ft_atoi(argv[4]) <= 0)
		return (error("'time_to_sleep' invalid", NULL, 0));
	if (argv[5] && (is_alpha_string(argv[5]) || ft_atoi(argv[5]) <= 0))
		return (error("'number_times_each_philo_must_eat' invalid", NULL, 0));
	return (0);
}

int	main(int argc, char **argv)
{
	t_program	program;

	if (argc < 5 || argc > 6)
		return (error("Invalid number of arguments", NULL, 0));
	if (check_args_input(argv) == 1)
		return (1);
	if (start(&program, argv, argc) == 1)
		return (1);
	if (create_threads(&program))
		return (1);
	exit_program(&program, 2);
	return (0);
}