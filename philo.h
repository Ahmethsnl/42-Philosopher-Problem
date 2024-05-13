/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ahmsanli <ahmsanli@student.42istanbul.c    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/05/03 14:45:43 by ahmsanli          #+#    #+#             */
/*   Updated: 2024/05/13 14:29:21 by ahmsanli         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <pthread.h>
# include <stdlib.h>
# include <sys/time.h>
# include <unistd.h>
# include <stdio.h>

# define ERROR 1
# define SUCCESS 0

typedef unsigned long long	t_time;

typedef struct s_philo
{
	int				id;
	int				c_eat;
	t_time			timer;
	t_time			last_meal;
	pthread_t		thread;
	struct s_data	*data;
}	t_philo;

typedef struct s_data
{
	int				death_timer;
	int				sleep_timer;
	int				philo_n;
	int				corpse;
	int				round;
	int				meal_timer;
	int				ac;
	char			**av;
	t_philo			*philo;
	pthread_mutex_t	*death;
	pthread_mutex_t	*forks;
}	t_data;

int		ft_exit(char *str);
int		ft_atoi(char *str);
int		data_init(t_data *data, int ac, char **av);
int		ft_checknum(char *str);
int		philo_init(t_data *data);
int		round_check(t_data *data);
int		mutex_init(t_data *data);
t_time	ft_time(void);
void	free_destroy(t_data *data);
int		ft_death_check(t_philo *philo, t_time time);
int		start_simulation(t_data *data);
void	*simulation(void *philo);
void	dinner_time(t_philo *philo);
int		monitor(t_data *data, t_time time);
void	ft_lastmeal(t_philo *philo);
void	free_destroy(t_data *data);
void	ft_write(int action, t_philo *ph, char *str, t_time time);
void	ft_sleep_time(t_philo *phi, int ttime);
void	checker(t_philo *philo, int checker);
void	aristoteles(t_philo *phi);

#endif