/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:43 by obibby            #+#    #+#             */
/*   Updated: 2023/03/01 18:41:35 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/EasterEgg.h"
#include <stdio.h>

extern inputsEE EasterEggLightsEE;

void	put_hex(FILE *output, int num)
{
	char	buff[4];

	for (int i = 2; i >= 0; i--)
	{
		buff[i] = "0123456789ABCDEF"[num % 16];
		num = num / 16;
	}
	buff[4] = 0;
	fputs(buff, output);
}

void	output_to_file(FILE *output)
{
	fputc(EasterEggLightsEE.AmbientLights + '0', output);
	put_hex(output, EasterEggLightsEE.AmbientLightsPWM);
	fputc(EasterEggLightsEE.BlinkLightLeft + '0', output);
	put_hex(output, EasterEggLightsEE.BlinkLightLeftPWM);
	fputc(EasterEggLightsEE.BrakeLights + '0', output);
	put_hex(output, EasterEggLightsEE.BrakeLightsPWM);
	fputc(EasterEggLightsEE.FogLights + '0', output);
	put_hex(output, EasterEggLightsEE.FogLightsPWM);
	fputc(EasterEggLightsEE.FrontLights + '0', output);
	put_hex(output, 0);
	fputc(EasterEggLightsEE.LicensePlateLight1 + '0', output);
	put_hex(output, EasterEggLightsEE.LicensePlateLight1PWM);
	fputc(EasterEggLightsEE.LicensePlateLight3 + '0', output);
	put_hex(output, EasterEggLightsEE.LicensePlateLight3PWM);
	fputc(EasterEggLightsEE.ParkingLightLeft + '0', output);
	put_hex(output, EasterEggLightsEE.ParkingLightLeftPWM);
	fputc(EasterEggLightsEE.ReverseLights + '0', output);
	put_hex(output, EasterEggLightsEE.ReverseLightsPWM);
}
