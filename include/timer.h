/* ************************************************************************** */
/*                                                                            */
/*                                                        ::::::::            */
/*   timer.h                                            :+:    :+:            */
/*                                                     +:+                    */
/*   By: joppe <jboeve@student.codam.nl>              +#+                     */
/*                                                   +#+                      */
/*   Created: 2023/06/19 09:17:13 by joppe         #+#    #+#                 */
/*   Updated: 2023/06/19 09:32:36 by joppe         ########   odam.nl         */
/*                                                                            */
/* ************************************************************************** */

#ifndef TIMER_H
#define TIMER_H

typedef struct s_timer 
{
	double start;
	double end;
	double delta;
	double (*time_func)(void);
} t_timer;


t_timer *timer_init(double (*time_func)(void));
void timer_free(t_timer *t);
double timer_start(t_timer *t);
double timer_stop(t_timer *t);
double timer_delta(t_timer *t);

#endif
