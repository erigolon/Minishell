/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vicrodri <vicrodri@student.42malaga.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/04/19 16:13:21 by vicrodri          #+#    #+#             */
/*   Updated: 2023/04/21 11:12:36 by vicrodri         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t count, size_t size)
{
	void	*s;

	s = malloc(count * size);
	if (s != NULL)
		ft_bzero(s, count * size);
	return (s);
}

/*The calloc() function contiguously allocates enough space for count objects
that are size bytes of memory each and returns a pointer to the allocated 
memory. The allocated memory is filled with bytes of value zero.

If successful, calloc() function return a pointer to allocated memory.  
If there is an error, they return a NULL pointer and set errno to ENOMEM.*/