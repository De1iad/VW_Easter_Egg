/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EasterEgg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:45:42 by obibby            #+#    #+#             */
/*   Updated: 2023/03/13 12:20:29 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/EasterEgg.h"
#include "../inc/car.h"
#include <sys/time.h>
#include "../ambientlights.h"
#include "../blinklights.h"
#include "../brakelights.h"
#include "../foglights.h"
#include "../frontlights.h"
#include "../license12.h"
#include "../license34.h"
#include "../parkinglights.h"
#include "../reverselights.h"

inputsEE EasterEggLightsEE;

void	*set_lights(void *time_void)
{
	time_t	*previous_time = time_void;
	time_t	previous = get_time_in_ms();
	time_t	current = get_time_in_ms();
	char	buff[3];
	int	i;

	while (current - *previous_time < 10800)
	{
		current = get_time_in_ms();
	}
	printf("lights current_time: %ld, prev_time: %ld\n", current, *previous_time);
	i = 0;
	while (1)
	{
		current = get_time_in_ms();
		if (current - previous >= 100)
		{
			if (i >= sizeof(ambientlights) / sizeof(uint16_t))
				return (NULL);
			if (ambientlights[i])
				EasterEggLightsEE.AmbientLights = 1;
			else
				EasterEggLightsEE.AmbientLights = 0;
			EasterEggLightsEE.AmbientLightsPWM = ambientlights[i];
			if (blinklights[i])
			{
				EasterEggLightsEE.BlinkLightLeft = 1;
				EasterEggLightsEE.BlinkLightRight = 1;
			}
			else
			{
				EasterEggLightsEE.BlinkLightLeft = 0;
				EasterEggLightsEE.BlinkLightRight = 0;
			}
			EasterEggLightsEE.BlinkLightLeftPWM = blinklights[i];
			EasterEggLightsEE.BlinkLightRightPWM = blinklights[i];
			if (brakelights[i])
				EasterEggLightsEE.BrakeLights = 1;
			EasterEggLightsEE.BrakeLightsPWM = brakelights[i];
			if (foglights[i])
				EasterEggLightsEE.FogLights = 1;
			else
				EasterEggLightsEE.FogLights = 0;
			EasterEggLightsEE.FogLightsPWM = foglights[i];
			if (frontlights[i])
				EasterEggLightsEE.FrontLights = 1;
			else
				EasterEggLightsEE.FrontLights = 0;
			if (licenseplate12[i])
			{
				EasterEggLightsEE.LicensePlateLight1 = 1;
				EasterEggLightsEE.LicensePlateLight2 = 1;
			}
			else
			{
				EasterEggLightsEE.LicensePlateLight1 = 0;
				EasterEggLightsEE.LicensePlateLight2 = 0;
			}
			EasterEggLightsEE.LicensePlateLight1PWM = licenseplate12[i];
			EasterEggLightsEE.LicensePlateLight2PWM = licenseplate12[i];
			if (licenseplate34[i])
			{
				EasterEggLightsEE.LicensePlateLight3 = 1;
				EasterEggLightsEE.LicensePlateLight4 = 1;
			}
			else
			{
				EasterEggLightsEE.LicensePlateLight3 = 0;
				EasterEggLightsEE.LicensePlateLight4 = 0;				
			}
			EasterEggLightsEE.LicensePlateLight3PWM = licenseplate34[i];
			EasterEggLightsEE.LicensePlateLight4PWM = licenseplate34[i];
			if (parkinglights[i])
			{
				EasterEggLightsEE.ParkingLightLeft = 1;
				EasterEggLightsEE.ParkingLightRight = 1;
			}
			else
			{
				EasterEggLightsEE.ParkingLightLeft = 0;
				EasterEggLightsEE.ParkingLightRight = 0;
			}
			EasterEggLightsEE.ParkingLightLeftPWM = parkinglights[i];
			EasterEggLightsEE.ParkingLightRightPWM = parkinglights[i];
			if (reverselights[i])
				EasterEggLightsEE.ReverseLights = 1;
			else
				EasterEggLightsEE.ReverseLights = 0;
			EasterEggLightsEE.ReverseLightsPWM = reverselights[i];
			previous = current;
			i++;
		}
	}
}