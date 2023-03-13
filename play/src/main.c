/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: cudoh <cudoh@student.42wolfsburg.de>       +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/01/27 16:02:37 by obibby            #+#    #+#             */
/*   Updated: 2023/02/25 11:37:3 by cudoh            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/car.h"

extern inputsEE EasterEggLightsEE;

time_t	get_time_in_ms(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * 1000) + (tv.tv_usec / 1000));
}

// puts frames per second to window, based on time to draw last frame.
void	put_fps(t_car *car)
{
	char	*tmp;
	char	*str;

	tmp = ft_itoa(1000 / (car->current_time - car->previous_time));
	str = ft_strjoin(tmp, "fps");
	free(tmp);
	mlx_string_put(car->mlx, car->window, 5, 10, colourshift(255, 0, 0, 0), str);
	free(str);
}

// puts car image and light image to window, updates light image with new values.
int	light_loop(t_car *car)
{
	car->current_time = get_time_in_ms();
	if (car->current_time - car->previous_time >= 10)
	{	
		//EasterEgg_Cyclic_10ms();
		brake_lights(car);
		indicators(car);
		main_lights(car);
		fog_lights(car);
		parking_lights(car);
		interior(car);
		license_plate(car);
		reverse_lights(car);
		mlx_put_image_to_window(car->mlx, car->window, car->image.img, 0, 0);
		mlx_put_image_to_window(car->mlx, car->window, car->alpha_image.img, 0, 0);
		put_fps(car);
		car->previous_time = car->current_time;
	}
	return (0);
}

int	main()
{
	t_car car;
	pthread_t	light_thread;
	pthread_t	song_thread;
	time_t		linked_time;
	int x;
	int y;

	car.previous_time = get_time_in_ms();
	car.mlx = mlx_init();
	car.window = mlx_new_window(car.mlx, 960, 782, "VW Easter Egg Demo");
	car.image.img = mlx_new_image(car.mlx, 960, 782);
	car.image.addr = mlx_get_data_addr(car.image.img, &car.image.bpp, &car.image.line_size, &car.image.endian);
	car.xpm.img = mlx_xpm_file_to_image(car.mlx, "images/car.xpm", &x, &y);
	car.xpm.addr = mlx_get_data_addr(car.xpm.img, &car.xpm.bpp, &car.xpm.line_size, &car.xpm.endian);
	put_image(&car.image, &car.xpm);
	mlx_destroy_image(car.mlx, car.xpm.img);
	car.alpha_image.img = make_image(car.mlx);
	car.alpha_image.addr = mlx_get_data_addr(car.alpha_image.img, &car.alpha_image.bpp, &car.alpha_image.line_size, &car.alpha_image.endian);
	linked_time = get_time_in_ms();
	pthread_create(&light_thread, NULL, set_lights, &linked_time);
	pthread_create(&song_thread, NULL, playSong, &linked_time);
	mlx_hook(car.window, 17, 0, ft_free, &car);
	mlx_loop_hook(car.mlx, light_loop, &car);
	mlx_loop(car.mlx);
	pthread_join(light_thread, NULL);
	pthread_join(song_thread, NULL);
}
