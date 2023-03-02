/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                   cudoh, nrenz, & obibby                */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include <stdio.h>
#include "../inc/EasterEgg.h"
#include <sys/time.h>

inputsEE EasterEggLightsEE;

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec * 0.001));
}

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

void	set_lights(void)
{
	FILE	*input = fopen("lights", "r");
	time_t	previous = get_time_in_ms();
	time_t	current = get_time_in_ms();
	char	buff[3];

	current = get_time_in_ms();
	if (current - previous >= 10)
	{
		EasterEggLightsEE.AmbientLights = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.AmbientLightsPWM = hex_to_dec(buff);
		EasterEggLightsEE.BlinkLightLeft = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.BlinkLightLeftPWM = hex_to_dec(buff);
		EasterEggLightsEE.BlinkLightRight = EasterEggLightsEE.BlinkLightLeft;
		EasterEggLightsEE.BlinkLightRightPWM = EasterEggLightsEE.BlinkLightLeftPWM;
		EasterEggLightsEE.BrakeLights = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.BrakeLightsPWM = hex_to_dec(buff);
		EasterEggLightsEE.FogLights = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.FogLightsPWM = hex_to_dec(buff);
		EasterEggLightsEE.FrontLights = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.LicensePlateLight1 = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.LicensePlateLight1PWM = hex_to_dec(buff);
		EasterEggLightsEE.LicensePlateLight2 = EasterEggLightsEE.LicensePlateLight1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;
		EasterEggLightsEE.LicensePlateLight3 = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.LicensePlateLight3PWM = hex_to_dec(buff);
		EasterEggLightsEE.LicensePlateLight4 = EasterEggLightsEE.LicensePlateLight3;
		EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;
		EasterEggLightsEE.ParkingLightLeft = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.ParkingLightLeftPWM = hex_to_dec(buff);
		EasterEggLightsEE.ParkingLightRight = EasterEggLightsEE.ParkingLightLeft;
		EasterEggLightsEE.ParkingLightRightPWM = EasterEggLightsEE.ParkingLightLeftPWM;
		EasterEggLightsEE.ReverseLights = fgetc(input) - '0';
		fread(buff, sizeof(char), 3, input);
		EasterEggLightsEE.ReverseLightsPWM = hex_to_dec(buff);
		previous = current;
	}
}
