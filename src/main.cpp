// Include standard headers
#include <stdio.h>
#include <stdlib.h>

#include <iostream>
#include "Gameworld.h"

#define GLEW_STATIC
#include <GL/glew.h>
#include <GLFW/glfw3.h>

int main(void)
{
	
	Gameworld my_game = Gameworld();
	my_game.init();
	my_game.init_gameworld();

	Color square_color = Color(1, 0, 0);
	float colorshade = 0.04f;


	do {
		
		for (int i = 10; i <= 30; i++) {
			my_game.set_pixel(i, 10, &square_color);
			my_game.set_pixel(i, 30, &square_color);
		}
		for (int j = 10; j <= 30; j++) {
			my_game.set_pixel(10, j, &square_color);
			my_game.set_pixel(30, j, &square_color);
		}
		my_game.redraw();

		if (square_color.r > 1 || square_color.r < 0)
			colorshade = -colorshade;

		square_color.r += colorshade;
		

	} while (my_game.is_not_over());

	my_game.cleanup();
	

	return 0; 
}
