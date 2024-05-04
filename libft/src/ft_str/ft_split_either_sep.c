/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split_readline_string.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: faboussa <faboussa@student.42lyon.fr>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/14 12:49:34 by faboussa          #+#    #+#             */
/*   Updated: 2024/03/14 12:49:34 by faboussa         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
//
// char **fill_array_with_quotes_management(char *s)
//{
//	size_t	i;
//	size_t	j;
//	size_t	len;
//	char quote;
//	char	**split;
//	size_t split_size;
//
//	if (s == NULL)
//		return (NULL);
//	deal_double_double_quotes_or_double_single_quotes(s);
//	split_size = count_letters_for_quotes(s) + 1 + count_letters_for_space(s)
//		+ 1;
//	split = ft_calloc(split_size, sizeof(char *));
//	if (split == NULL)
//		return (NULL);
//	i = 0;
//	j = 0;
//	while (s[i] != '\0')
//	{
//		len = 0;
//		if (s[i] && (s[i] == '\"' || s[i] == '\''))
//		{
//			quote = s[i++];
//			while (s[i + len] && s[i + len] != quote)
//				len++;
//			split[j] = ft_substr(s, i, len);
//			if (split[j] == NULL)
//			{
//				ft_free_all_tab(split);
//				return (NULL);
//			}
//			j++;
//			i += len;
//			if (s[i] == quote)
//				i++;
//		}
//		else if (s[i] && s[i] != ' ')
//		{
//			while (s[i + len] && s[i + len] != ' ')
//				len++;
//			split[j] = ft_substr(s, i, len);
//			if (split[j] == NULL)
//			{
//				ft_free_all_tab(split);
//				return (NULL);
//			}
//			j++;
//			i += len;
//		}
//		else
//			i++;
//	}
//	split[j] = NULL;
//	return (split);
//}