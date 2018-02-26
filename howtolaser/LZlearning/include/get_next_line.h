/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jquenel <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/11/17 00:39:01 by jquenel           #+#    #+#             */
/*   Updated: 2017/11/22 11:25:12 by jquenel          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFF_SIZE
#  define BUFF_SIZE			4
# endif
# ifndef EOL
#  define EOL				'\n'
# endif

# include "libft.h"

typedef struct	s_stock
{
	char			buf[BUFF_SIZE + 1];
	int				fd;
	struct s_stock	*next;
}				t_stock;

int				get_next_line(const int fd, char **line);

#endif
