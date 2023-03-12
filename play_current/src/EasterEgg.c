/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   EasterEgg.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 18:45:42 by obibby            #+#    #+#             */
/*   Updated: 2023/03/04 11:26:03 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdio.h>
#include "../inc/EasterEgg.h"
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
time_t	get_time_in_ms(void);

// time_t	get_time_in_ms(void)
// {
// 	struct timeval	tv;

// 	gettimeofday(&tv, NULL);
// 	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
// }

int	hex_to_dec(char *hex)
{
	int	dec;
	int	base;

	dec = 0;
	base = 1;
	for (int i = 3; i > 0; i--)
	{
		if (hex[i] >= '0' && hex[i] <= '9')
		{
			dec += (hex[i] - '0') * base;
			base *= 16;
		}
		else if (hex[i] >= 'A' && hex[i] <= 'F')
		{
			dec += (hex[i] - 55) * base;
			base *= 16;
		}
	}
	return (dec);
}

void	*set_lights(void *time_void)
{
	FILE	*input = fopen("lights", "r");
	time_t	*previous_time = time_void;
	time_t	previous = get_time_in_ms();
	time_t	current = get_time_in_ms();
	char	buff[3];
	int	i;

	while (current - *previous_time < 11000)
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
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.AmbientLightsPWM = hex_to_dec(buff);
			// EasterEggLightsEE.BlinkLightLeft = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.BlinkLightLeftPWM = hex_to_dec(buff);
			// EasterEggLightsEE.BlinkLightRight = EasterEggLightsEE.BlinkLightLeft;
			// EasterEggLightsEE.BlinkLightRightPWM = EasterEggLightsEE.BlinkLightLeftPWM;
			// EasterEggLightsEE.BrakeLights = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.BrakeLightsPWM = hex_to_dec(buff);
			// EasterEggLightsEE.FogLights = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.FogLightsPWM = hex_to_dec(buff);
			// EasterEggLightsEE.FrontLights = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.LicensePlateLight1 = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.LicensePlateLight1PWM = hex_to_dec(buff);
			// EasterEggLightsEE.LicensePlateLight2 = EasterEggLightsEE.LicensePlateLight1;
			// EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;
			// EasterEggLightsEE.LicensePlateLight3 = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.LicensePlateLight3PWM = hex_to_dec(buff);
			// EasterEggLightsEE.LicensePlateLight4 = EasterEggLightsEE.LicensePlateLight3;
			// EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;
			// EasterEggLightsEE.ParkingLightLeft = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.ParkingLightLeftPWM = hex_to_dec(buff);
			// EasterEggLightsEE.ParkingLightRight = EasterEggLightsEE.ParkingLightLeft;
			// EasterEggLightsEE.ParkingLightRightPWM = EasterEggLightsEE.ParkingLightLeftPWM;
			// EasterEggLightsEE.ReverseLights = fgetc(input) - '0';
			// fread(buff, sizeof(char), 3, input);
			// EasterEggLightsEE.ReverseLightsPWM = hex_to_dec(buff);
			previous = current;
			if (feof(input))
				return (0);
			i++;
		}
	}
}