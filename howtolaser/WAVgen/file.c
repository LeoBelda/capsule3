/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:33:02 by lbelda            #+#    #+#             */
/*   Updated: 2018/02/13 09:27:55 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavgen.h"

int			prep_file(void)
{
	int		fd;
	char	*path = PATH;

	fd = 0;
	if (!(fd = open(path, O_WRONLY | O_CREAT | O_TRUNC, 0777)))
		error_exit("Couldnt create file", E_FATAL);
	return (fd);
}
