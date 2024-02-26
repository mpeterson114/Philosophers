#include "philo.h"

int	is_alpha_string(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] < '0' || str[i] > '9')
			return (1);
		i++;
	}
	return (0);
}

int	ft_atoi(char *str)
{
	int			i;
	int			sign;
	long int	result;

	if (str == NULL)
		return (0);
	i = 0;
	sign = 1;
	result = 0;
	if (str[i] == '+' || str[i] == '-')
	{
		if (str[i] == '-')
			sign *= -1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = (result * 10) + (str[i] - '0');
		i++;
	}
	return (result * sign);
}

long	current_time_m(void)
{
	struct timeval	time;

	if (gettimeofday(&time, NULL))
		return (error("gettimeofday() error\n", NULL, 4));
	return ((time.tv_sec * 1000) + (time.tv_usec / 1000));
}

int	ft_usleep(size_t millisec)
{
	size_t	s_time;

	s_time = current_time_m();
	while ((current_time_m() - s_time) < millisec)
		usleep(millisec / 10);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] && s2[i] && s1[i] == s2[i])
		i++;
	return (s1[i] - s2[i]);
}
