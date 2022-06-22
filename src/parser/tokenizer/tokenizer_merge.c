/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tokenizer_merge.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kanghyki <kanghyki@student.42seoul.kr>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/06/16 15:51:20 by kanghyki          #+#    #+#             */
/*   Updated: 2022/06/23 00:40:48 by kanghyki         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../include/minishell.h"

static void	ft_no_quote(t_lexer *lexer, char quote);

void	ft_merge_env(t_lexer *lexer)
{
	char	*value;
	t_env	*node;

	ft_read_lexer(lexer);
	if (ft_cur_char(lexer) == '?')
	{
		lexer->pa_str = ft_merge_str(lexer->pa_str, ft_itoa(g_exit));
		ft_read_lexer(lexer);
		return ;
	}
	ft_set_spos(lexer);
	while (ft_strchr(M_SEP, ft_cur_char(lexer)) == NULL
		&& ft_cur_char(lexer) != '\n' && ft_cur_char(lexer) != '=')
		ft_read_lexer(lexer);
	if ((ft_cur_ptr(lexer) - ft_get_spos(lexer)) > 0)
	{
		node = ft_env_search(ft_get_env(lexer), ft_strndup(ft_get_spos(lexer), \
					ft_cur_ptr(lexer) - ft_get_spos(lexer)));
		if (node != NULL)
			lexer->pa_str = ft_merge_str(lexer->pa_str, \
					ft_strdup(node->pa_value));
	}
	else
		lexer->pa_str = ft_merge_str(lexer->pa_str, ft_strdup("$"));
}

void	ft_merge_quote(t_lexer *lexer, char quote)
{
	ft_set_spos(lexer);
	while (ft_cur_char(lexer) != '\0')
	{
		if (ft_cur_char(lexer) == quote)
		{
			ft_save_str(lexer);
			return (ft_read_lexer(lexer));
		}
		else if (quote == '"' && ft_cur_char(lexer) == M_ENV)
		{
			ft_save_str(lexer);
			ft_merge_env(lexer);
			ft_set_spos(lexer);
		}
		else
			ft_read_lexer(lexer);
	}
	printf("Unclosed Quote\n");
}
