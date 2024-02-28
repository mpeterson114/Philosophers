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
	pthread_mutex_t	death_mutex;
	pthread_mutex_t	meal_mutex;
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

/* init.c */
void	args_fill(t_program *program, char **argv, char argc);
void	init_philos(t_program *program);
int		init_forks(t_program *program);
int		init_program(t_program *program, char **argv, char argc);
int		start(t_program *program, char **argv, int argc);

/* threads.c */
int		death_checker(t_philo *philo);
void	*philo_routine(void *ph_pointer);
int		create_threads(t_program *program);

/* monitor.c */
void	write_message(char *str, t_philo *philo, int id);
int	time_checker(t_philo *philo);
int	meal_checker(t_philo *philo);
void *monitor_routine(void *ph_pointer);

/* utils */
int		is_alpha_string(char *str);
int		ft_atoi(char *str);
long	current_time_m(void);
int		ft_usleep(size_t millisec);
int		ft_strcmp(char *s1, char *s2);



#endif