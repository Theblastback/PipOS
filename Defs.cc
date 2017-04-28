#include "./Headers/Defs.h"

// NODE RELATED FUNCTIONS /////////////////////////////////////////////////////////////////////////////
Defs::node * Defs :: mkNode(char *Path, int X, int Y, int Width, int Height, int Color) {
	 Defs::node *Tmp = (struct node *) malloc(sizeof(struct node));

	// Setting the rectangular coordinates
  	Tmp -> Rect.x = X;
	Tmp -> Rect.y = Y;
	Tmp -> Rect.w = Width;
	Tmp -> Rect.h = Height;

	// Checking if node is a background rect or a clock image
	if ( Path != NULL ) { // Placing an image onto here
		Tmp -> Image = IMG_Load(Path);
	} else if ( Color != 0 ) { // Creating a rectangle
		Tmp -> Image = SDL_CreateRGBSurface(0, Width, Height, 32, rmask, gmask, bmask, amask);
		SDL_Rect Temp = Tmp -> Rect;
		SDL_FillRect(Tmp -> Image, &Temp, SDL_MapRGB(Tmp -> Image -> format, (Color >> 16), ((Color >> 8) & 255), (Color & 255)));
	} else { // Error getting input
		free(Tmp);
 	}

	Tmp -> There = NULL;
	return(Tmp);
}
// QUEUE RELATED FUNCTIONS ///////////////////////////////////////////////////////////////////////////

Defs::queue * Defs :: mkQueue() {
	struct queue *Tmp = (struct queue *) malloc(sizeof(struct queue));
	Tmp -> Start = NULL;
	Tmp -> End = NULL;
	return(Tmp);
}

void Defs :: Enqueue(Defs::queue *Main, Defs::node *Tmp) {
	if ( Main != NULL ) { // Making sure Queue exists
		if ( Main -> Start != NULL ) { 		// Something already in the queue
			Tmp -> There = Main -> Start;
			Main -> Start = Tmp;
		} else {				// First one in the queue
			Main -> Start = Tmp;
			Main -> End = Tmp;
		}
	}
}

void Defs :: Dequeue(Defs::queue *Main) {
	Defs::node *Tmp;
	if ( Main != NULL ) { // Making sure the queue itself exists
		if ( Main -> Start != NULL ) { // Making sure there aren't any nodes in here
			Tmp = Main -> Start;
			if (Tmp -> There != NULL) {
				while (Tmp -> There != Main -> End) { // Loop until end
					Tmp = Tmp -> There;
				}
			}
			if ( (Main -> Start == Tmp) && (Main -> End == Tmp) ) { // Checking if this is the last node in the queue
				free_Node(Main -> End);
				Main -> Start = NULL;
				Main -> End = NULL;
			} else {
				free_Node(Main -> End);
				Main -> End = Tmp;
				Tmp -> There = NULL;
			}
		}
	}
}

void Defs :: Free_Queue(Defs::queue *Main) {
	if ( Main != NULL ) { // Mo point in freeing a non existant queue
		Defs::node *Tmp = Main -> Start;
		while ( Tmp != NULL ) { // Frees nodes until tmp reaches end of list
			Main -> Start = Tmp -> There;
			free_Node(Tmp);
			Tmp = Main -> Start;
		}
	}
}

// Universal functions /////////////////////////////////////////////////////////////////////////////////
///// Initializations //////////////////////////////////////////////////////////////////////////////////

void Defs :: init_SDL() {										// Start up SDL and initialize the fonts
	if ( SDL_Init(SDL_INIT_EVERYTHING) != 0 ) { // Get all of the goodies of sdl started up
		fprintf(stderr, "Couldn't init SDL: %s\n", SDL_GetError());
		exit(1);
	}
	// Start of PNG expansion
	if ( IMG_Init(IMG_INIT_PNG) != IMG_INIT_PNG ) {
		fprintf(stderr, "Couldn't init png support: %s \n", IMG_GetError());
		exit(2);
	}
	SDL_ShowCursor(SDL_DISABLE);
}


///// Freeing Statements /////////////////////////////////////////////////////////////////////////////
void Defs :: free_Node(Defs::node *Node) {						// Free either type of node in program
	if ( Node != NULL ) {
		if (Node -> Image != NULL)
			SDL_FreeSurface(Node -> Image);
		else
			fprintf(stderr, "No image was detected!\n");

		free(Node);
		Node = NULL;
	}
}


void Defs :: free_SDL() {										// Exit out of all SDL initializations

	// Exit SDL_Image
	IMG_Quit();

	// Clean up and exit SDL2
	SDL_Quit();
}
