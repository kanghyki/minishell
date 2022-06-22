/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_free_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanghyki <kanghyki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/12 04:34:39 by kanghyki          #+#    #+#             */
/*   Updated: 2022/06/22 17:50:08 by kanghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

void	ft_free_argument(t_argument *arg)
{
	t_argument	*prev;
	int			i;

	prev = arg;
	while (arg != NULL)
	{
		i = 0;
		while (arg->pa_argument[i] != NULL)
		{
			free(arg->pa_argument[i]);
			++i;
		}
		free(arg->pa_argument);
		arg = arg->next;
		free(prev);
		prev = arg;
	}
}
