#include "Headers/Render.h"

void Render :: Set_Foreground(Defs::queue *Queue) {
	Foreground = Queue;
}

void Render :: Pulse() {
	if ( Repetition >= 4 ) { // 2 seconds have passed since last node of pulse was deallocated
		node *Tmp = NULL;
		if ( (ListAmount < 20) ) { // New pulse as List number is empty and List is empty
			// Make Tmp node
			int Color = ((int)Red << 16) | ((int)Green << 8) | ((int)Blue);
			Tmp = mkNode(NULL, 0, 0, 800, 4, Color); // Create a node and allocate a surface for it

			// Since these are floats, I've got to reduce these amounts linearly to make the color go back to normal
			Red = Red - 0.5;
			Green = Green - 3;
			Blue = Blue - 1.35;

			ListAmount++;
			Enqueue(Background, Tmp);
		}


		Tmp = Background -> Start;


		while (Tmp != NULL) {
			if ( Tmp -> Rect.y > 800 ) { // Tmp is off screen
				Dequeue(Background); // Seg faults here
				if (Background -> Start == NULL) { // Emptied out list
					Repetition = 0;
					ListAmount = 0;
					Red = 18;
					Green = 101;
					Blue = 49;
				}
				break; // No point in continuing since all other nodes before this one have been freed
			}

			// Change the Y position of the pulse line
			Tmp -> Rect.y = (int)(Tmp -> Rect.y) + 8; // 4 for Y coordinates, 4 for rect box
			// Advance forward one position in the queue
			Tmp = Tmp -> There;
		}
	} else
		Repetition++; // Wait 2 seconds until the pulse is complete

}

void Render :: Refresh() { // Redo the entire screen into the background
	// Darker color 4, 24, 13, 255
	// lighter color 7, 41, 22, 255
	// X: 0 - 800
	// Y: 0 - 480
	node *FG_Tmp; // Foreground temporary node

	SDL_Rect Rect;
	Rect.x	= 0;
	Rect.w	= 800;
	Rect.h	= 4;
	Rect.y = 0;

	SDL_Surface *Tmp = SDL_CreateRGBSurface(0, 800, 4, 32, rmask, gmask, bmask, amask);

	while ( Rect.y < 480 ) {
		if ( (Rect.y / 4) & 1 ) { // Checking if this is the lighter color
			SDL_FillRect(Tmp, NULL, SDL_MapRGB(Tmp -> format, 4, 24, 13));
		} else { // Darker color selected
			SDL_FillRect(Tmp, NULL, SDL_MapRGB(Tmp -> format, 7, 41, 22));
		}
		SDL_BlitSurface(Tmp, NULL, Main_Render, &Rect);
		Rect.y = Rect.y + 4;
	}
	SDL_FreeSurface(Tmp);


	FG_Tmp = Foreground -> Start; // Reset the pointer to the start of the Foreground queue
	while (FG_Tmp != NULL) {
		Rect = FG_Tmp -> Rect;
		SDL_BlitSurface(FG_Tmp -> Image, NULL, Main_Render, &Rect);

		FG_Tmp = FG_Tmp -> There;
	}

	SDL_UpdateWindowSurface(Main_Window);

}


void Render :: render() {
	node *BG_Tmp; // Background temporary node
	SDL_Rect	Surf_Conv;

	if ( (Background != NULL) && (Background -> Start != NULL) ) { // Perform this ONLY if there is something in the background
		BG_Tmp = Background -> Start; // Begin this operation

		while (BG_Tmp != NULL) { // Loop until the end of the queue
			Surf_Conv = BG_Tmp -> Rect;
			SDL_BlitSurface(BG_Tmp -> Image, NULL, Main_Render, &Surf_Conv); // Re-do the pulse effect
			// Advance forward in the background queue
			BG_Tmp = BG_Tmp -> There;
		}
		SDL_UpdateWindowSurface(Main_Window);
	}
}


void Render :: init_render() {
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
		rmask = 0xff000000;
		gmask = 0x00ff0000;
		bmask = 0x0000ff00;
		amask = 0x000000ff;
	#else
		rmask = 0x000000ff;
		gmask = 0x0000ff00;
		bmask = 0x00ff0000;
		amask = 0xff000000;
	#endif

	// Create the window and renderer
	if ( (Main_Window = SDL_CreateWindow("PipOS", SDL_WINDOWPOS_UNDEFINED,
						      SDL_WINDOWPOS_UNDEFINED, 800, 480, SDL_WINDOW_SHOWN)) == 0  ) {
		fprintf(stderr, "Couldn't init window & renderer: %s\n", SDL_GetError());
		exit(4);
	} else {
		Main_Render = SDL_GetWindowSurface(Main_Window);
	}
	// Allocate data for the queues that hold the information regarding the visual background and foregrounds
	Background = mkQueue();
	Foreground = mkQueue();

	// These amounts are used with the pulse function
	Repetition = 0;		// Is to delay the initiation of a new "pulse" after the last one ends
	ListAmount = 0;		// Tells how many items are in the list proper

	// Sets the original RGB of the colors that make the pulse
	Red = 18;
	Green = 101;
	Blue = 49;

}

void Render :: free_render() {
	Free_Queue(Background);
	Free_Queue(Foreground);

	SDL_FreeSurface(Main_Render);
	SDL_DestroyWindow(Main_Window);
}
