/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   output_to_file.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: obibby <obibby@student.42wolfsburg.de>     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/03/01 14:02:43 by obibby            #+#    #+#             */
/*   Updated: 2023/03/07 09:01:29 by obibby           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/EasterEgg.h"
#include <stdio.h>
#include "../inc/WavLib.h"

extern inputsEE EasterEggLightsEE;

void	put_hex(FILE *output, int num)
{
	char	buff[4];

	fputs("0x", output);
	for (int i = 2; i >= 0; i--)
	{
		buff[i] = "0123456789ABCDEF"[num % 16];
		num = num / 16;
	}
	buff[3] = 0;
	fputs(buff, output);
}

void	write_array_footer(FILE *output)
{
	fwrite("\n};\n", 1, 4, output);
}

void	write_array_header(FILE *output, char *name)
{
	fwrite("const uint16_t ", 1, 15, output);
	fwrite(name, 1, strlen(name), output);
	fwrite("[] = {\n", 1, 7, output);
}

void	put_footers_to_file(t_info *info)
{
	write_array_footer(info->ambientlights);
	write_array_footer(info->blinklights);
	write_array_footer(info->brakelights);
	write_array_footer(info->foglights);
	write_array_footer(info->frontlights);
	write_array_footer(info->licenseplate12);
	write_array_footer(info->licenseplate34);
	write_array_footer(info->parkinglights);
	write_array_footer(info->reverselights);
}

void	put_headers_to_file(t_info *info)
{
	write_array_header(info->ambientlights, "ambientlights");
	write_array_header(info->blinklights, "blinklights");
	write_array_header(info->brakelights, "brakelights");
	write_array_header(info->foglights, "foglights");
	write_array_header(info->frontlights, "frontlights");
	write_array_header(info->licenseplate12, "licenseplate12");
	write_array_header(info->licenseplate34, "licenseplate34");
	write_array_header(info->parkinglights, "parkinglights");
	write_array_header(info->reverselights, "reverselights");
}

void	output_to_file(int16_t code, t_info *info)
{
	static int init;
	
	if (code == WAVLIB_EOF)
	{
		put_footers_to_file(info);
		fclose(info->ambientlights);
		fclose(info->blinklights);
		fclose(info->brakelights);
		fclose(info->foglights);
		fclose(info->frontlights);
		fclose(info->licenseplate12);
		fclose(info->licenseplate34);
		fclose(info->parkinglights);
		fclose(info->reverselights);
		return ;
	}
	if (!init)
	{
		info->ambientlights = fopen("ambientlights.h", "w+");
		info->blinklights = fopen("blinklights.h", "w+");
		info->brakelights = fopen("brakelights.h", "w+");
		info->foglights = fopen("foglights.h", "w+");
		info->frontlights = fopen("frontlights.h", "w+");
		info->licenseplate12 = fopen("license12.h", "w+");
		info->licenseplate34 = fopen("license34.h", "w+");
		info->parkinglights = fopen("parkinglights.h", "w+");
		info->reverselights = fopen("reverselights.h", "w+");
		put_headers_to_file(info);
		put_hex(info->ambientlights, EasterEggLightsEE.AmbientLightsPWM);
		put_hex(info->blinklights, EasterEggLightsEE.BlinkLightLeftPWM);
		put_hex(info->brakelights, EasterEggLightsEE.BrakeLightsPWM);
		put_hex(info->foglights, EasterEggLightsEE.FogLightsPWM);
		put_hex(info->frontlights, EasterEggLightsEE.FrontLights);
		put_hex(info->licenseplate12, EasterEggLightsEE.LicensePlateLight1PWM);
		put_hex(info->licenseplate34, EasterEggLightsEE.LicensePlateLight3PWM);
		put_hex(info->parkinglights, EasterEggLightsEE.ParkingLightLeftPWM);
		put_hex(info->reverselights, EasterEggLightsEE.ReverseLightsPWM);
		init = 1;
		return ;
	}
	fwrite(", ", sizeof(char), 2, info->ambientlights);
	put_hex(info->ambientlights, EasterEggLightsEE.AmbientLightsPWM);
	fwrite(", ", sizeof(char), 2, info->blinklights);
	put_hex(info->blinklights, EasterEggLightsEE.BlinkLightLeftPWM);
	fwrite(", ", sizeof(char), 2, info->brakelights);
	put_hex(info->brakelights, EasterEggLightsEE.BrakeLightsPWM);
	fwrite(", ", sizeof(char), 2, info->foglights);
	put_hex(info->foglights, EasterEggLightsEE.FogLightsPWM);
	fwrite(", ", sizeof(char), 2, info->frontlights);
	put_hex(info->frontlights, EasterEggLightsEE.FrontLights);
	fwrite(", ", sizeof(char), 2, info->licenseplate12);
	put_hex(info->licenseplate12, EasterEggLightsEE.LicensePlateLight1PWM);
	fwrite(", ", sizeof(char), 2, info->licenseplate34);
	put_hex(info->licenseplate34, EasterEggLightsEE.LicensePlateLight3PWM);
	fwrite(", ", sizeof(char), 2, info->parkinglights);
	put_hex(info->parkinglights, EasterEggLightsEE.ParkingLightLeftPWM);
	fwrite(", ", sizeof(char), 2, info->reverselights);
	put_hex(info->reverselights, EasterEggLightsEE.ReverseLightsPWM);
	// //fputc(EasterEggLightsEE.AmbientLights + '0', output);
	// //fputc(EasterEggLightsEE.BlinkLightLeft + '0', output);
	// put_hex(output, EasterEggLightsEE.BlinkLightLeftPWM);
	// //fputc(EasterEggLightsEE.BrakeLights + '0', output);
	// put_hex(output, EasterEggLightsEE.BrakeLightsPWM);
	// //fputc(EasterEggLightsEE.FogLights + '0', output);
	// put_hex(output, EasterEggLightsEE.FogLightsPWM);
	// //fputc(EasterEggLightsEE.FrontLights + '0', output);
	// put_hex(output, 0);
	// //fputc(EasterEggLightsEE.LicensePlateLight1 + '0', output);
	// put_hex(output, EasterEggLightsEE.LicensePlateLight1PWM);
	// //fputc(EasterEggLightsEE.LicensePlateLight3 + '0', output);
	// put_hex(output, EasterEggLightsEE.LicensePlateLight3PWM);
	// //fputc(EasterEggLightsEE.ParkingLightLeft + '0', output);
	// put_hex(output, EasterEggLightsEE.ParkingLightLeftPWM);
	// //fputc(EasterEggLightsEE.ReverseLights + '0', output);
	// put_hex(output, EasterEggLightsEE.ReverseLightsPWM);
}
