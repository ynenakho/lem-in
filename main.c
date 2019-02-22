/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ynenakho <ynenakho@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/02/21 19:55:03 by ynenakho          #+#    #+#             */
/*   Updated: 2019/02/21 22:40:08 by ynenakho         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lemin.h"

int main(int argc, char const *argv[])
{
    t_lemin lemin;

    ft_bzero(&lemin, sizeof(t_lemin));
    read_stdin(&lemin);
    
    ft_putstr(lemin.input);
    return (0);
}

// int	go_gnl(int i, char **line)
// {
// 	if (*line)
// 	{
// 		ft_bzero(*line, ft_strlen(*line));
// 		free(*line);
// 	}
// 	return (get_next_line(i, line));
// }
void check_num_of_ants(char *line, t_lemin *lemin)
{
    int int_to_check;
    int_to_check = ft_atoi(line);
    if(!ft_strcmp(line, ft_itoa(int_to_check)))
        lemin->num_of_ants = int_to_check;
    else
        exit_error("Number of ants is in a wrong format: ", line);
}



void read_stdin(t_lemin *lemin) {
    char *line;
    int run_count = 1;
    while (get_next_line(0, &line)) {
        if (run_count++ == 1) 
            check_num_of_ants(line, lemin);
        // if (run_count)
    }
}
            