/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cpapot <cpapot@student.42lyon.fr >         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/19 16:21:03 by cpapot            #+#    #+#             */
/*   Updated: 2023/02/25 16:49:20 by cpapot           ###   ########.fr       */
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

# define EAT			"\x1b[36mis eating\x1b[0m"
# define THINK			"\x1b[33mis thinking\x1b[0m"
# define SLEEP			"\x1b[35mis sleeping\x1b[0m"
# define DEAD			"died\x1b[0m"
# define FORK			"\x1b[32mhas taken a fork\x1b[0m"

typedef struct s_memstock
{
	void				*content;
	struct s_memstock	*next;
}						t_memlist;

typedef struct s_tab
{
	int			*fork_tab;
	pthread_t	*philo;
}			t_tab;

typedef struct s_info
{
	int					nb_of_philo;
	int					time_to_die;
	int					time_to_eat;
	int					time_to_sleep;
	int					nb_philo_eat;
	int					is_alive;
	long				creation_time;
	pthread_mutex_t		print_mutex;
	pthread_mutex_t		dead_mutex;
	pthread_mutex_t		*fork_mutex;
}			t_info;

typedef struct s_philo
{
	int					actual_philo;
	int					eat_count;
	long				last_eat;
	int					can_eat;
	int					right_fork;
	int					left_fork;
	struct s_info		*info;

}				t_philo;
/*				parsing					*/
void			print_error(char *error);
void			check_error(int argc, char **argv);
t_info			parsing(int argc, char **argv);

/*				philo_utils				*/
long long		ft_atoll(const char *str);
size_t			ft_strlen(const char *str);
t_philo			*ft_philonew(int content, t_info *info, t_memlist **memlist);
void			lock_print(t_philo *info, char *str, int philo_nb);
void			set_last_eat(t_philo *info);

/*				fork					*/
pthread_mutex_t	*create_fork_tab(int philo_nb, t_memlist **memlist);
void			check_fork(t_philo *info);
void			reset_fork(t_philo *info);

/*				process					*/
void			*philo_process(void *p_data);

/*				stockmem				*/
void			stock_free(t_memlist **stock);
void			*stock_malloc(size_t size, t_memlist **stock);

#endif
