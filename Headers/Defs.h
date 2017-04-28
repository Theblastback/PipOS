#ifndef DEFS_H
#define DEFS_H

#include <SDL2/SDL.h>
#include "SDL2/SDL_image.h"


class Defs {
	public:
		// Node stucture
		struct node {
			struct node	*There;
			SDL_Surface	*Image; // Surface of which the rectangle is colored with
			SDL_Rect	Rect; // Background rectangle | will mostly remain unchanged
			Uint32		Color; // Color of rectangle
		};

		// Queue structure
		struct queue {
			struct node *Start;
			struct node *End;
		};

		// FUNCTION BEGIN ////////////////////////////////////////////////////////////////////////////////////////////


		// Background Node manipulation function
		struct node * mkNode(char *, int, int, int, int, int); // PNG Path, X, Y, Width, Height, Color

		// Queue manipulation function
		struct queue * mkQueue();

		void Enqueue(struct queue *, struct node *); // Point of Node and Node being in there is to make this a universal insert
		void Dequeue(struct queue *); // Will only remove and free last node.
		void Free_Queue(struct queue *); // Will free the entire queue. Useful for exiting the program.

		// Initialization functions
		void init_SDL(); // Initialize all parts of sdl we will use

		// Freeing functions
		void free_Node(struct node *); // Will free any node
		void free_SDL(); // Exit out of SDL

		// Rendering cruds
		Uint32 rmask, gmask, bmask, amask;
		SDL_Surface	*Main_Render;
		SDL_Window	*Main_Window;

		struct queue	*Background;
		struct queue	*Foreground;

	private:

};

#endif
