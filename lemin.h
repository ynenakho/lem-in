/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lemin.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:58:16 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/21 22:29:25 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEMIN_H
# define LEMIN_H
# include "libft/libft.h"

typedef struct  s_lemin
{
    int     num_of_ants;
    char    *input;
}               t_lemin;


void read_stdin(t_lemin *lemin);
void exit_error(char *msg, char* arg);

#endif