/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                   cudoh, nrenz, & obibby                */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "EasterEgg.h"

inputsEE EasterEggLightsEE;

void	EasterEgg_Cyclic_10ms(void)
{
	static uint8_t	interval = 10;
	static int		i;
	char			buff[3];

	if (interval == 10)
	{
		if (i >= sizeof(ambientlights) / sizeof(uint16_t))
			return ;

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
		else
			EasterEggLightsEE.BrakeLights = 0;
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
			EasterEggLightsEE.LicensePlateLight5 = 1;
		}
		else
		{
			EasterEggLightsEE.LicensePlateLight1 = 0;
			EasterEggLightsEE.LicensePlateLight2 = 0;
			EasterEggLightsEE.LicensePlateLight5 = 0;
		}
		EasterEggLightsEE.LicensePlateLight1PWM = licenseplate12[i];
		EasterEggLightsEE.LicensePlateLight2PWM = licenseplate12[i];
		EasterEggLightsEE.LicensePlateLight5PWM = licenseplate12[i];

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

		interval = 0;
		i++;
		return ;
	}
	interval++;
}
