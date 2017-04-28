#include <stdio.h>
#include <stdlib.h>
#include "Headers/Defs.h"
#include "Headers/Render.h"
#include "Headers/Clock.h"


int main (int argc, char **argv) {
	SDL_Event	e;
	Defs		defs;
	Render		render;
	Clock		time;
	Uint32		Time_Pacer, Time_Passed;
	int		Hour, Minute;


	// Initialize all of my functions
	defs.init_SDL();
	render.init_render();

	// Set the time
	fprintf(stdout, "Type in the current hour:\t");
	fscanf(stdin, "%d", &Hour);
	fprintf(stdout, "Type in the current minute\t");
	fscanf(stdin, "%d", &Minute);

	time.Set_Clock(Hour, Minute);


	// Link the Time to the render function's foreground
	render.Set_Foreground(time.Get_Time_Queue());

	render.Refresh();


	Time_Passed = SDL_GetTicks(); // Gets the current time
	while (1) {
		Time_Pacer = SDL_GetTicks();
		SDL_PollEvent(&e);

		if ( e.type== SDL_KEYDOWN ) // Escape key sequence
			if ( e.key.keysym.sym == SDLK_ESCAPE ) // pressed q
				break;


		render.Pulse();
		render.render();

		if ( SDL_GetTicks() - Time_Passed >= 60000 ) { // At least 1 minute has passed
			Time_Passed = SDL_GetTicks(); // Let this record first for a more accurate minute regulator
			time.Incriment(); // Increase minute total by one
			render.Refresh();
		}

		// This is my FPS Cap. Currently caps at 30 FPS
		if ( (Time_Pacer = SDL_GetTicks() - Time_Pacer) < 33 ) // Will only delay if framerate could be higher than 30
			SDL_Delay(33 - Time_Pacer); // Will give everything a 30 fps
		else
			printf("Below fps threshold\n ms Per Frame: %d\n\n", Time_Pacer);



	}

	time.Free_Queue(time.Get_Time_Queue());
	render.free_render();
	defs.free_SDL();
	return 0;
}
