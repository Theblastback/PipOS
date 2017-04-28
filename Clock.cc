#include "Headers/Clock.h"

void Clock :: Set_Clock(int Start_H, int Start_M) { // Start_Hour, Start_Minute
	// Just set the hour and minute variables immediately so that I don't forget
	Hour = Start_H;
	Min = Start_M;

	Time = mkQueue(); // Have to make a queue for the time list

	// X Coordinates will go 50, 195, 340, 485, 630; This will give a 25 pixel buffer between each digit
	// Y's are all 64
	// W: 120	H: 272

	Hour_1 = mkNode("./Pics/Clock_Pics/Colon.png", 40, 64, 120, 272, 0);
	Hour_2 = mkNode("./Pics/Clock_Pics/Colon.png", 195, 64, 120, 272, 0);
	Colon = mkNode("./Pics/Clock_Pics/Colon.png", 320, 64, 120, 272, 0);
	Min_1 = mkNode("./Pics/Clock_Pics/Colon.png", 445, 64, 120, 272, 0);
	Min_2 = mkNode("./Pics/Clock_Pics/Colon.png", 615, 64, 120, 272, 0);

	// Change the numbers to the correct amount
	Change_Number(Hour_1, (Hour / 10)); // Creates the tens place digit
	Change_Number(Hour_2, (Hour % 10)); // Creates the ones place digit
	Change_Number(Min_1, (Min / 10)); // Creates the tens place digit
	Change_Number(Min_2, (Min % 10)); // Creates the ones place digit

	// Throw all the numbers into the queue
	Enqueue(Time, Hour_1);
	Enqueue(Time, Hour_2);
	Enqueue(Time, Colon);
	Enqueue(Time, Min_1);
	Enqueue(Time, Min_2);
}

Defs::queue * Clock :: Get_Time_Queue() {
	return(Time);
}

void Clock :: Incriment() {
	// Increase the minutes by one
	Min++;

	// Will only increase if 60 nminutes have gone by, and will not go past 24 hours
	Hour = (Hour + (Min / 60)) % 24;

	// Keep minutes in line
	Min = Min % 60;

	// Change any and all possible number changes
	Change_Number(Hour_1, (Hour / 10)); // Creates the tens place digit
	Change_Number(Hour_2, (Hour % 10)); // Creates the ones place digit
	Change_Number(Min_1, (Min / 10)); // Creates the tens place digit
	Change_Number(Min_2, (Min % 10)); // Creates the ones place digit

}

void Clock :: Change_Number(node *Store, unsigned char Number) {
	if ( Store -> Image != NULL ) { // Get rid of the old image before setting up the new one
		SDL_FreeSurface(Store -> Image);
	}
	// Use this to select which number to load
	switch (Number) {
		case(0):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Zero.png");
			break;

		case(1):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/One.png");
			break;

		case(2):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Two.png");
			break;

		case(3):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Three.png");
			break;

		case(4):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Four.png");
			break;

		case(5):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Five.png");
			break;

		case(6):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Six.png");
			break;

		case(7):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Seven.png");
			break;

		case(8):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Eight.png");
			break;

		case(9):
			Store -> Image = IMG_Load("./Pics/Clock_Pics/Nine.png");
			break;

	}
}
