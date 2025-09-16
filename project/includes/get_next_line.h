/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jaemyu <jaemyu@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/22 21:26:22 by jaemyu            #+#    #+#             */
/*   Updated: 2025/05/23 18:58:54 by jaemyu           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

# include <fcntl.h>
# include <stdlib.h>
# include <unistd.h>

int		gnl_strlen(const char *str);
char	*gnl_strjoin(char *str1, char *str2);
char	*gnl_strdup(char *str);
int		new_line_check(char *str);
char	*mine_line(int fd, char *buf, char *storage);
char	*residue(char *line);
char	*get_next_line(int fd);
void	buf_free(char **storage, char **buf);

#endif