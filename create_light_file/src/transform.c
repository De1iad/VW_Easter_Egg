
/* ********************************************************************** */
/*                                                                        */
/*    VW - EASTER EGG PROJECT                                             */
/*    42Wolfsburg                                                         */
/*    2022/2023                                                           */
/*                                                                        */
/* ********************************************************************** */

#include "../inc/WavLib.h"
#include "../inc/EasterEgg.h"
#include <sys/time.h>

//# define WAVFILE ("./quantumania.wav")

inputsEE EasterEggLightsEE;

double **get_averages(tstSampleBufferDouble *sample_freqs);

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

void	manual_assign_freqs(t_light_freqs *freqs)
{
	freqs->Ambient_Lights = 0;
	freqs->Blink_Lights = 0;
	freqs->Brake_Lights = 0;
	freqs->Fog_Lights = 0;
	freqs->Front_Lights = 0;
	freqs->License_Light1 = 0;
	freqs->License_Light2 = 0;
	freqs->License_Light3 = 0;
	freqs->License_Light4 = 0;
	freqs->License_Light5 = 0;
	freqs->Parking_Lights = 0;
	freqs->Reverse_Lights = 0;
}

void	auto_assign_freqs(t_light_freqs *freqs, double *max_amp)
{
	double	magnitude = 0;
	for (int i = 80; i < 100; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Front_Lights = i;
			magnitude = max_amp[i];
		}
	}
	//printf("front lights: %dhz\n", freqs->Front_Lights);
	magnitude = 0;
	for (int i = 10; i < 100; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Fog_Lights = i;
			magnitude = max_amp[i];
		}
	}
	//printf("fog lights: %dhz\n", freqs->Fog_Lights);
	magnitude = 0;
	for (int i = 400; i < 700; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Blink_Lights = i;
			magnitude = max_amp[i];
		}
	}
	//printf("blink lights: %dhz\n", freqs->Blink_Lights);
	magnitude = 0;
	for (int i = 40; i < 50; i++)
	{
		if (max_amp[i] > magnitude && freqs->Fog_Lights != i)
		{
			freqs->Ambient_Lights = i;
			magnitude = max_amp[i];
		}
	}
	//printf("ambient lights: %dhz\n", freqs->Ambient_Lights);
	magnitude = 0;
	for (int i = 880; i < 900; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->License_Light1 = i;
			freqs->License_Light2 = i;
			magnitude = max_amp[i];
		}
	}
	//printf("license lights 1-2: %dhz\n", freqs->License_Light1);
	magnitude = 0;
	for (int i = 2130; i < 2136; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->License_Light3 = i;
			freqs->License_Light4 = i;
			magnitude = max_amp[i];
		}
	}
	//printf("license lights 3-4: %dhz\n", freqs->License_Light3);
	magnitude = 0;
	for (int i = 5000; i < 5500; i++)
	{
		if (max_amp[i] > magnitude)
		{
			freqs->Reverse_Lights = i;
			magnitude = max_amp[i];
		}
	}
}

// void	active_assign_freqs(tstSampleBufferDouble *sample_freqs, t_light_freqs *freqs)
// {
// 	double	magnitude = 0;
// 	for (int i = 80; i < 100; i++)
// 	{
// 		if (sample_freqs->dStereoL[i] > magnitude)
// 		{
// 			freqs->Front_Lights = i;
// 			magnitude = max_amp[i];
// 		}
// 	}
// 	printf("front lights: %dhz\n", freqs->Front_Lights);
// 	magnitude = 0;
// 	for (int i = 10; i < 50; i++)
// 	{
// 		if (max_amp[i] > magnitude)
// 		{
// 			freqs->Fog_Lights = i;
// 			magnitude = max_amp[i];
// 		}
// 	}
// 	printf("fog lights: %dhz\n", freqs->Fog_Lights);
// 	magnitude = 0;
// 	for (int i = 400; i < 700; i++)
// 	{
// 		if (max_amp[i] > magnitude)
// 		{
// 			freqs->Blink_Lights = i;
// 			magnitude = max_amp[i];
// 		}
// 	}
// 	printf("blink lights: %dhz\n", freqs->Blink_Lights);
// 	magnitude = 0;
// 	for (int i = 40; i < 50; i++)
// 	{
// 		if (max_amp[i] > magnitude && freqs->Fog_Lights != i)
// 		{
// 			freqs->Ambient_Lights = i;
// 			magnitude = max_amp[i];
// 		}
// 	}
// 	printf("ambient lights: %dhz\n", freqs->Ambient_Lights);
// 	magnitude = 0;
// 	for (int i = 880; i < 900; i++)
// 	{
// 		if (max_amp[i] > magnitude)
// 		{
// 			freqs->License_Light1 = i;
// 			freqs->License_Light2 = i;
// 			magnitude = max_amp[i];
// 		}
// 	}
// 	printf("license lights 1-2: %dhz\n", freqs->License_Light1);
// 	magnitude = 0;
// 	for (int i = 2130; i < 2136; i++)
// 	{
// 		if (max_amp[i] > magnitude)
// 		{
// 			freqs->License_Light3 = i;
// 			freqs->License_Light4 = i;
// 			magnitude = max_amp[i];
// 		}
// 	}
// 	printf("license lights 3-4: %dhz\n", freqs->License_Light3);
// }

int	check_average(tstSampleBufferDouble * sample_freqs, double *max_amp, int start, int end)
{
	double	average;
	double	max_avg;
	
	average = 0;
	max_avg = 0;
	for (int i = start; i <= end; i++)
	{
		average += sample_freqs->dStereoL[i];
		average += sample_freqs->dStereoR[i];
		max_avg += max_amp[i];
	}
	average = average / (end + 1 - start);
	max_avg = max_avg / (end + 1 - start);
	if (average > max_avg * 0.55)
		return (1);
	return (0);
}

void	set_light_variables(tstSampleBufferDouble *sample_freqs, t_light_freqs *freqs, double *max_amp)
{
	// double **averages = get_averages(sample_freqs);
	// for (int i = 0; i < 19; i++)
	// 	printf("freq range %d-%d: %f\n", i * 8, (i + 1) * 8, averages[0][i]);
	// free(averages);

	//printf("%f / 7 = %f, current freq L: %f, current freq R: %f\n", max_amp[freqs->Front_Lights], max_amp[freqs->Front_Lights] / 7, sample_freqs->dStereoL[freqs->Front_Lights], sample_freqs->dStereoR[freqs->Front_Lights]);
	//printf("timestamp: %ld\n", get_time_in_ms());
	// for (int i = 0; i < 22050; i++)
	// {
	// 	if ((sample_freqs->dStereoL[i] > 1000) || (sample_freqs->dStereoR[i] > 1000))
	// 		printf("freq %d, left: %f, right: %f, max_amp: %f\n", i, sample_freqs->dStereoL[i], sample_freqs->dStereoR[i], max_amp[i]);
	// }

	// headlights
	if (check_average(sample_freqs, max_amp, 53, 57))
	{
		EasterEggLightsEE.FrontLights = 1;
	}
	else
		EasterEggLightsEE.FrontLights = 0;

	// fog lights
	if (sample_freqs->dStereoL[freqs->Fog_Lights] > max_amp[freqs->Fog_Lights] / 3)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Fog_Lights] / max_amp[freqs->Fog_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Fog_Lights] > max_amp[freqs->Fog_Lights] / 3)
	{
		EasterEggLightsEE.FogLights = 1;
		EasterEggLightsEE.FogLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Fog_Lights] / max_amp[freqs->Fog_Lights]);
	}
	else
	{
		if (EasterEggLightsEE.FogLightsPWM)
		{
			if (EasterEggLightsEE.FogLightsPWM < 100)
				EasterEggLightsEE.FogLightsPWM = 0;
			else
				EasterEggLightsEE.FogLightsPWM -= 100;
		}
		else
			EasterEggLightsEE.FogLights = 0;
	}

	// parking lights
	if (sample_freqs->dStereoL[73] > max_amp[73] / 5)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (sample_freqs->dStereoL[73] / max_amp[73]);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (sample_freqs->dStereoL[73] / max_amp[73]);
	}
	else if (sample_freqs->dStereoR[73] > max_amp[73] / 5)
	{
		EasterEggLightsEE.ParkingLightLeft = 1;
		EasterEggLightsEE.ParkingLightLeftPWM = 1000 * (sample_freqs->dStereoR[73] / max_amp[73]);
		EasterEggLightsEE.ParkingLightRight = 1;
		EasterEggLightsEE.ParkingLightRightPWM = 1000 * (sample_freqs->dStereoR[73] / max_amp[73]);
	}
	else
	{
		if (EasterEggLightsEE.ParkingLightLeftPWM)
		{
			if (EasterEggLightsEE.ParkingLightLeftPWM < 100)
			{
				EasterEggLightsEE.ParkingLightLeftPWM = 0;
				EasterEggLightsEE.ParkingLightRightPWM = 0;
			}
			else
			{
				EasterEggLightsEE.ParkingLightLeftPWM -= 100;
				EasterEggLightsEE.ParkingLightRightPWM -= 100;
			}
		}
		else
		{
			EasterEggLightsEE.ParkingLightLeft = 0;
			EasterEggLightsEE.ParkingLightRight = 0;			
		}
	}

	// blink lights
	if (sample_freqs->dStereoL[freqs->Blink_Lights] > max_amp[freqs->Blink_Lights] / 5) // old: sample_freqs->dStereoL[876] > max_amp[876] / 7
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoL[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoL[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Blink_Lights] > max_amp[freqs->Blink_Lights] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoR[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoR[freqs->Blink_Lights] / max_amp[freqs->Blink_Lights]);
	}
	else if (sample_freqs->dStereoL[700] > max_amp[700] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoL[700] / max_amp[700]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoL[700] / max_amp[700]);
	}
	else if (sample_freqs->dStereoR[700] > max_amp[700] / 5)
	{
		EasterEggLightsEE.BlinkLightLeft = 1;
		EasterEggLightsEE.BlinkLightLeftPWM = 1000 * (sample_freqs->dStereoR[700] / max_amp[700]);
		EasterEggLightsEE.BlinkLightRight = 1;
		EasterEggLightsEE.BlinkLightRightPWM = 1000 * (sample_freqs->dStereoR[700] / max_amp[700]);
	}
	else
	{
		if (EasterEggLightsEE.BlinkLightLeftPWM)
		{
			if (EasterEggLightsEE.BlinkLightLeftPWM < 100)
			{
				EasterEggLightsEE.BlinkLightLeftPWM = 0;
				EasterEggLightsEE.BlinkLightRightPWM = 0;				
			}
			else
			{
				EasterEggLightsEE.BlinkLightLeftPWM -= 100;
				EasterEggLightsEE.BlinkLightRightPWM -= 100;
			}
		}
		else
		{
			EasterEggLightsEE.BlinkLightLeft = 0;
			EasterEggLightsEE.BlinkLightRight = 0;
		}
	}

	// brake lights
	if (sample_freqs->dStereoL[2365] > max_amp[2365] / 5) //556
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (sample_freqs->dStereoL[2365] / max_amp[2365]);
	}
	else if (sample_freqs->dStereoR[2365] > max_amp[2365] / 5)
	{
		EasterEggLightsEE.BrakeLights = 1;
		EasterEggLightsEE.BrakeLightsPWM = 1000 * (sample_freqs->dStereoR[2365] / max_amp[2365]);
	}
	else
	{
		if (EasterEggLightsEE.BrakeLightsPWM)
		{
			if (EasterEggLightsEE.BrakeLightsPWM < 100)
				EasterEggLightsEE.BrakeLightsPWM = 0;
			else
				EasterEggLightsEE.BrakeLightsPWM -= 100;
		}
		else
			EasterEggLightsEE.BrakeLights = 0;
	}

	// ambient lights
	if (sample_freqs->dStereoL[freqs->Ambient_Lights] > max_amp[freqs->Ambient_Lights] / 5)
	{
		EasterEggLightsEE.AmbientLights = 1;
		EasterEggLightsEE.AmbientLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Ambient_Lights] / max_amp[freqs->Ambient_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Ambient_Lights] > max_amp[freqs->Ambient_Lights] / 5)
	{
		EasterEggLightsEE.AmbientLights = 1;
		EasterEggLightsEE.AmbientLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Ambient_Lights] / max_amp[freqs->Ambient_Lights]);
	}
	else
	{
		if (EasterEggLightsEE.AmbientLightsPWM > 0)
		{
			if (EasterEggLightsEE.AmbientLightsPWM < 100)
				EasterEggLightsEE.AmbientLightsPWM = 0;
			else
				EasterEggLightsEE.AmbientLightsPWM -= 100;
		}
		else
			EasterEggLightsEE.AmbientLights = 0;
	}
	
	// license lights 1-2
	if (sample_freqs->dStereoL[freqs->License_Light1] > max_amp[freqs->License_Light1] / 5)
	{
		EasterEggLightsEE.LicensePlateLight1 = 1;
		EasterEggLightsEE.LicensePlateLight1PWM = 1000 * (sample_freqs->dStereoL[freqs->License_Light1] / max_amp[freqs->License_Light1]);
		EasterEggLightsEE.LicensePlateLight2 = 1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;

	}
	else if (sample_freqs->dStereoR[freqs->License_Light1] > max_amp[freqs->License_Light1] / 5)
	{
		EasterEggLightsEE.LicensePlateLight1 = 1;
		EasterEggLightsEE.LicensePlateLight1PWM = 1000 * (sample_freqs->dStereoR[freqs->License_Light1] / max_amp[freqs->License_Light1]);
		EasterEggLightsEE.LicensePlateLight2 = 1;
		EasterEggLightsEE.LicensePlateLight2PWM = EasterEggLightsEE.LicensePlateLight1PWM;
	}
	else
	{
		if (EasterEggLightsEE.LicensePlateLight1PWM > 0)
		{
			if (EasterEggLightsEE.LicensePlateLight1PWM < 100)
			{
				EasterEggLightsEE.LicensePlateLight1PWM = 0;
				EasterEggLightsEE.LicensePlateLight2PWM = 0;
			}
			else
			{
				EasterEggLightsEE.LicensePlateLight1PWM -= 100;
				EasterEggLightsEE.LicensePlateLight2PWM -= 100;
			}
		}
		else
		{
			EasterEggLightsEE.LicensePlateLight1 = 0;
			EasterEggLightsEE.LicensePlateLight2 = 0;
		}	
	}

	// license lights 3-4
	if (sample_freqs->dStereoL[freqs->License_Light3] > max_amp[freqs->License_Light3] / 5)
	{
		EasterEggLightsEE.LicensePlateLight3 = 1;
		EasterEggLightsEE.LicensePlateLight3PWM = 1000 * (sample_freqs->dStereoL[freqs->License_Light3] / max_amp[freqs->License_Light3]);
		EasterEggLightsEE.LicensePlateLight4 = 1;
		EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;

	}
	else if (sample_freqs->dStereoR[freqs->License_Light3] > max_amp[freqs->License_Light3] / 5)
	{
		EasterEggLightsEE.LicensePlateLight3 = 1;
		EasterEggLightsEE.LicensePlateLight3PWM = 1000 * (sample_freqs->dStereoR[freqs->License_Light3] / max_amp[freqs->License_Light3]);
		EasterEggLightsEE.LicensePlateLight4 = 1;
		EasterEggLightsEE.LicensePlateLight4PWM = EasterEggLightsEE.LicensePlateLight3PWM;
	}
	else
	{
		if (EasterEggLightsEE.LicensePlateLight3PWM)
		{
			if (EasterEggLightsEE.LicensePlateLight3PWM < 100)
			{
				EasterEggLightsEE.LicensePlateLight3PWM = 0;
				EasterEggLightsEE.LicensePlateLight4PWM = 0;
			}
			else
			{
				EasterEggLightsEE.LicensePlateLight3PWM -= 100;
				EasterEggLightsEE.LicensePlateLight4PWM -= 100;
			}
		}
		else
		{
			EasterEggLightsEE.LicensePlateLight3 = 0;
			EasterEggLightsEE.LicensePlateLight4 = 0;
		}
	}

	// reverse lights
	if (sample_freqs->dStereoL[freqs->Reverse_Lights] > max_amp[freqs->Reverse_Lights] / 5)
	{
		EasterEggLightsEE.ReverseLights = 1;
		EasterEggLightsEE.ReverseLightsPWM = 1000 * (sample_freqs->dStereoL[freqs->Reverse_Lights] / max_amp[freqs->Reverse_Lights]);
	}
	else if (sample_freqs->dStereoR[freqs->Reverse_Lights] > max_amp[freqs->Reverse_Lights] / 5)
	{
		EasterEggLightsEE.ReverseLights = 1;
		EasterEggLightsEE.ReverseLightsPWM = 1000 * (sample_freqs->dStereoR[freqs->Reverse_Lights] / max_amp[freqs->Reverse_Lights]);
	}
	else
	{
		if (EasterEggLightsEE.ReverseLightsPWM)
		{
			if (EasterEggLightsEE.ReverseLightsPWM < 100)
				EasterEggLightsEE.ReverseLightsPWM = 0;
			else
				EasterEggLightsEE.ReverseLightsPWM -= 100;
		}
		else
			EasterEggLightsEE.ReverseLights = 0;
	}
}

void	*transform_loop(void *info_void)
{   
	t_info			*info = info_void;
	t_light_freqs	freqs;
	tenWavLibReturnCode	retval;

	//manual_assign_freqs(&freqs);
	auto_assign_freqs(&freqs, info->max_amp);
	fseek(info->wav.wavStream, info->wav.wavReadConfig.u32FileSeekPosL, SEEK_SET);  
	while (1)
	{
			retval = WAVLIB_LoadSampleFromStreamToBuffer(info->wav.wavStream,
															&info->wav.wavReadConfig, 
															&info->wav.wavSampleBufferHex,
															wavSpec);
			if (retval == WAVLIB_EOF)
			{
				output_to_file(WAVLIB_EOF, info);
				return (NULL);
			}
			WAVLIB_ConvertSampleBufferToFloatByChannel(
														&info->wav.wavSampleBufferHex,
														&info->wav.wavSampleBufferFloatInp,
														&info->wav.wavReadConfig);
			WAVLIB_TransformFloatSample(
														&info->wav.wavSampleBufferFloatInp,
														&info->wav.wavSampleBufferFreq,
														&info->wav.wavReadConfig);
			set_light_variables(&info->wav.wavSampleBufferFreq, &freqs, info->max_amp);
			output_to_file(0, info);
			info->wav.wavReadConfig.u32FileSeekPosL -= (info->wav.wavReadConfig.u32Offset * (44100 - 4410));
			info->wav.wavReadConfig.u32FileSeekPosR -= (info->wav.wavReadConfig.u32Offset * (44100 - 4410));
	}
	return (NULL);
}

int transform(t_info *info)
{
    tenWavLibReturnCode     wavReturnCode;

    wavReturnCode = WAVLIB_ERR_FILE_OPEN;
    info->wav.wavStream = NULL;
    memset((void *)&info->wav.wavSampleBufferHex, 0, (sizeof(tstSampleBufferHex)));
    memset((void *)&info->wav.wavSampleBufferFloatInp, 0, (sizeof(tstSampleBufferFloat)));
    memset((void *)&info->wav.wavSampleBufferFreq, 0, (sizeof(tstSampleBufferHex)));
    memset((void *)&info->wav.wavReadConfig, 0, (sizeof(tstWavReadConfig)));

    /* Load wav file */
    info->wav.wavStream = fopen(info->input, "rb");
    if (info->wav.wavStream == NULL)
    {
        printf("Error open file, %d\n", wavReturnCode);
        return (wavReturnCode);
    }

    /* Load wav file audio specification data */
	if (!wavSpec[0].u32SpecData)
	{
		wavReturnCode = WAVLIB_LoadSpecData(info->wav.wavStream, wavSpec);
		if (wavReturnCode != WAVLIB_SUCCESS)
		{
			printf("Error load spec data, %d\n", wavReturnCode);
			fclose(info->wav.wavStream);
			return (wavReturnCode);
		}
	}
    /* Display wav file audio specification data */
    WAVLIB_ShowWavSpec(wavSpec);

    /* Initialise the configuration for reading samples from wav file */
    WAVLIB_ReadConfigInit(&info->wav.wavReadConfig, wavSpec);
    printf("seekposL: %d, seekposR: %d, idx: %d, offset: %d, byteCnt: %d\n",
                                        info->wav.wavReadConfig.u32FileSeekPosL,
                                        info->wav.wavReadConfig.u32FileSeekPosR,
                                        info->wav.wavReadConfig.u32Idx,
                                        info->wav.wavReadConfig.u32Offset,
                                        info->wav.wavReadConfig.u8ByteCnt);
	return (0);
}

void fetch_amp_range(t_info *info)
{
	int return_code = 0;
	long i = 0;

    for (int i = 0; i < 22050; i++)
		info->max_amp[i] = 0;
	fseek(info->wav.wavStream, info->wav.wavReadConfig.u32FileSeekPosL, SEEK_SET);
	//int total_samples = 0;
    while (return_code != WAVLIB_EOF) //total_samples < wavSpec[6].u32SpecData
	{
		i++;
		return_code = WAVLIB_LoadSampleFromStreamToBuffer(info->wav.wavStream,
														&info->wav.wavReadConfig, 
														&info->wav.wavSampleBufferHex,
														wavSpec);

		// - convert sample data to float
		WAVLIB_ConvertSampleBufferToFloatByChannel(
													&info->wav.wavSampleBufferHex,
													&info->wav.wavSampleBufferFloatInp,
													&info->wav.wavReadConfig);


		// - perform transform - freq 
		WAVLIB_TransformFloatSample(
													&info->wav.wavSampleBufferFloatInp,
													&info->wav.wavSampleBufferFreq,
													&info->wav.wavReadConfig);
		for (int x=0; x < 22050; x++)
		{
		    if (info->wav.wavSampleBufferFreq.dStereoL[x] > info->max_amp[x])
		    {
		        info->max_amp[x] = info->wav.wavSampleBufferFreq.dStereoL[x];
		    }
		    if (info->wav.wavSampleBufferFreq.dStereoR[x] > info->max_amp[x])
		    {
		        info->max_amp[x] = info->wav.wavSampleBufferFreq.dStereoR[x];
		    }
		}
		info->wav.wavReadConfig.u32FileSeekPosL -= (info->wav.wavReadConfig.u32Offset * (44100 - 4410));
		info->wav.wavReadConfig.u32FileSeekPosR -= (info->wav.wavReadConfig.u32Offset * (44100 - 4410));
	}
	printf("loops: %ld\n", i);
	printf("done\n");
	// for (int x=0; x < 22050; x++)
	// {
	// 	if (info->max_amp[x] > 200)
	// 		printf("freq %d max: %f\n", x, info->max_amp[x]);
	// }
	// exit(0);
}

double **get_averages(tstSampleBufferDouble *sample_freqs)
{
	double **averages = calloc(sizeof(double *), 2);
	int j;

	averages[0] = calloc(sizeof(double), 19);
	averages[1] = calloc(sizeof(double), 19);
	j = 0;
	for (int i = 0; i < 152; i++)
	{
		//max
		if (sample_freqs->dStereoL[i] > averages[0][j]) // with 15 samples if max sample size of 2280 and pools of 152
			averages[0][j] = sample_freqs->dStereoL[i]; // with 19 samples if max sample size of 152 and pools of 8
		if (sample_freqs->dStereoR[i] > averages[1][j])
			averages[1][j] = sample_freqs->dStereoR[i];
		if (i == 8 * (j + 1))
			j++;
		//mean
		// averages[0][j] += sample_freqs->dStereoL[i];
		// averages[1][j] += sample_freqs->dStereoR[i];
		// if (i == 152 * (j + 1))
		// {
		// 	averages[0][j] /= 152;
		// 	averages[1][j] /= 152; //570 pools if 7980 total, 1575 if 22050 total. Assuming 14 samples.
		// 	j++;
		// }
	}
	return (averages);
}

int	main(int argc, char *argv[])
{
	t_info	info;

	if (argc != 2)
	{
		printf("Usage: ./create_file <source.wav>\n");
		return (1);
	}
	info.input = argv[1];
	//info.output = fopen("lights", "w+");
	transform(&info);
	fetch_amp_range(&info);
	fclose(info.wav.wavStream);
	transform(&info);
	transform_loop(&info);
	fclose(info.wav.wavStream);
	// fclose(info.output);
	return (0);
}