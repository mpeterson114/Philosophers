#ifndef PHILO_H
# define PHILO_H

# include <stdio.h>
# include <unistd.h>
# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>

typedef struct s_philo	t_philo;

typedef struct s_program
{
	long			start_time;
	int				time_to_eat;
	int				time_to_sleep;
	int				time_to_die;
	int				num_meals;
	int				num_of_philos;
	int				dead;
	// char			*shared_fork;
	t_philo			*philos;
	// pthread_t		*ph_tid;
	pthread_mutex_t	*forks;
	pthread_mutex_t	message_mutex;
	pthread_mutex_t	philo_die;
	pthread_mutex_t	prog_lock;  //meal lock?
}	t_program;

typedef struct s_philo
{
	int				id;
	int				meals_eaten;
    int             eating;
	long			last_meal;
    long            start_time;
    pthread_t       thread;
	// int				forks;
	t_program		*program;
	pthread_mutex_t *r_fork;
    pthread_mutex_t *l_fork;
	// pthread_mutex_t	philo_lock;
}	t_philo;

/* main.c */
int		check_args_input(char **argv);
void	free_program(t_program *program, int release);
void	exit_program(t_program *program, int release);
int		error(char *str, t_program *program, int release);


#endif