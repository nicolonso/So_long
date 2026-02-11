/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   so_long.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/11 12:08:15 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/11 18:02:12 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SO_LONG_H
# define SO_LONG_H

// Libraries

# include "../Lib/hdr/libft.h"
# include "../minilibx-linux/mlx.h"
# include "../minilibx-linux/mlx_int.h"
# include <unistd.h>
# include <stdlib.h>
# include <limits.h>
# include <fcntl.h>
# include <stdio.h>

// Get_next line Function
char	*get_next_line(int fd);

// Utilities of my get_next_line
size_t	ft_strlen(const char *str);
char	*ft_strjoin(char *s1, char *s2);
char	*ft_check_nl(const char *s, int c);
char	*extract_line(char *buffer);
char	*buffer_rest(char *buffer);

//Structure for my get_nexline
# ifndef BUFFER_SIZE
# define BUFFER_SIZE 10
# endif


#endif