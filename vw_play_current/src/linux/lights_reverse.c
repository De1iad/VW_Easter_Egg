/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lights_reverse.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/06 08:35:29 by obibby            #+#    #+#             */
/*   Updated: 2023/03/06 08:53:57 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../inc/car.h"

void	reverse_rear(t_car *car)
{
	int		x;
	int		y;
	double	alpha;

	if (!EasterEggLightsEE.ReverseLights)
		alpha = 0;
	else
		alpha = EasterEggLightsEE.ReverseLightsPWM * 0.0009;
	x = 640;
	while (++x < 823)
	{
		y = 180;
		while (++y < 190)
				put_pixel(&car->alpha_image, x, y, colourshift(255 * alpha, 252 * alpha, 3 * alpha, 3 * alpha));
	}
}

void	reverse_lights(t_car *car)
{
	reverse_rear(car);
}
