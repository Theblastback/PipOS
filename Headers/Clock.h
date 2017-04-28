#ifndef CLOCK_H
#define CLOCK_H

#include "Defs.h"

class Clock : public Defs {
	public:
		void Set_Clock(int, int); // Get the initial time for this program
		queue *Get_Time_Queue(); // Will simply return the queue that holds the assembled digits of the current time
		void Incriment();	// Main will check to see if a minute has passed; If so, increate the minute count by one


	private:
		void	Change_Number(node *, unsigned char); // Change the image of the node in question

		struct queue	*Time;		// Queue that holes all of the time information
		unsigned char	Hour;	// Holds the hour (0 - 23)
		unsigned char	Min;	// Holds the minute (0-59)

		// These queue hold the png arrangement for the time
		struct node	*Hour_1; // First Position of the hour
		struct node	*Hour_2; // Socond Position of the hour
		struct node	*Min_1;	// First Position of the minute
		struct node	*Min_2;	// Second postion of the minute
		struct node	*Colon;	// Hold the colon of the clock
};


#endif
