/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:03 by cpapot            #+#    #+#             */
/*   Updated: 2023/01/24 15:03:28 by cpapot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILOSOPHERS_H

# define PHILOSOPHERS_H

# include <unistd.h>
# include <stdio.h>
# include <stdlib.h>
# include <stdlib.h>
# include <pthread.h>
# include <sys/time.h>

# define RESET			"\x1b[0m"
# define BLACK			"\x1b[30m"
# define RED			"\x1b[31m"
# define GREEN			"\x1b[32m"
# define YELLOW			"\x1b[33m"
# define BLUE			"\x1b[34m"
# define MAGENTA		"\x1b[35m"
# define CYAN			"\x1b[36m"
# define WHITE			"\x1b[37m"

# define INT_MAX		2147483647
# define INT_MIN		-2147483647
# define LLONG_MAX		9223372036854775807
# define LLONG_MIN		-9223372036854775807

typedef struct s_info
{
	int					nb_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_philo_eat;
	int					is_alive;
	pthread_mutex_t		mutex;
	int					*fork_tab;
}			t_info;

typedef struct s_philo
{
	int					actual_philo;
	int					eat_count;
	long				creation_time;
	struct s_info		*info;

}				t_philo;
/*				parsing					*/
void			print_error(char *error);
void			check_error(int argc, char **argv);
t_info			parsing(int argc, char **argv);

/*				philo_utils				*/
long long		ft_atoll(const char *str);
size_t			ft_strlen(const char *str);
void			ft_philoadd_back(t_philo **lst, t_philo *new);
t_philo			*ft_philonew(int content, t_info *info);

/*				eat_philo				*/
void			eat_philo(t_philo *info);

#endif
