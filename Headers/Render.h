#ifndef PULSE_H
#define PULSE_H

#include "Defs.h"

class Render : Defs {
	public:
		void Pulse();			// Apply pulse effect overlay; Queue is background queue
		void Refresh(); 		// "Blit" background over everything
		void render();			// Render background, then foreground

		void init_render();
		void free_render();

		void Set_Foreground(struct queue*);		// Just to set the forground, so that I can render it

		// Background will have the highlighted color, followed by pigment background
		struct queue	*Background;	// Pulse values
		struct queue	*Foreground;	// List of whatever is on the screen

	private:
		// For pulse
		unsigned char 	Repetition;
		unsigned char 	ListAmount;
		unsigned char 	Red;
		unsigned char 	Blue;
		unsigned char 	Green;

};

#endif
