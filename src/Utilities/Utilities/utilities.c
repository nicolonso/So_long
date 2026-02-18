/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utilities.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:55:12 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/18 20:52:22 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"

// I need to test if its working when i send to them a new line

int ft_so_strlen(char *str)
{
	int	i;
	
	i = -1;
	while (str[++i] && str[i] != '\n');

	return (i);
}

int main(int ac, char **av)
{
	if (ac == 2)
	{
		int len = ft_so_strlen(av[1]);
		printf("len : %i", len);
	}
	return (0);
}
