/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: lbelda <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/13 08:40:44 by lbelda            #+#    #+#             */
/*   Updated: 2018/02/13 09:22:39 by lbelda           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "wavgen.h"

void	error_exit(char *err_str, enum e_err type)
{
	printf("%s\n", err_str);
	if (type == E_FATAL)
		exit(EXIT_FAILURE);
	else
		return ;
}
