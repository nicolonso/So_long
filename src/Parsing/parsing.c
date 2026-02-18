/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nalfonso <nalfonso@student.42lisboa.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2026/02/17 18:47:20 by nalfonso          #+#    #+#             */
/*   Updated: 2026/02/17 23:43:17 by nalfonso         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../hdr/so_long.h"


/* 
	I need to create a parsing that handle the follow values when I send the Ber Files through get next line
	Ber Files
	Values in this file

	- 1 -> Wall
	- 0 -> Empty Floor 
	- P -> Player
	- C -> Collectible 
	- E -> Exit

*/

/* typedef struct s_stack_parsing
{
	int			Wall;
	int			Floor;
	Bool		Player;
	Bool		Collectible;
	Bool		Exit;
}	t_stack_parsing; */


int ft_parsing(char *str)
{
	int static line;
	
	while (str[i] )

		if (line == 1 && str[i] != '1')
			i++;
			
}