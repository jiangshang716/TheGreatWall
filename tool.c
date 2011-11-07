#include "main.h"
#include "tool.h"
SDL_Surface *load_image( char* filename , int format) {
	//The image that's loaded 
	SDL_Surface* loadedImage = NULL; 
	SDL_Surface* optimizedImage = NULL; 
	//Load the image 
	loadedImage = IMG_Load( filename ); 
	if(loadedImage == NULL)
	{
		printf("image load failed\n");
		exit(2);
	}
	//If the image loaded 
	if( loadedImage != NULL && format == 1) { 
		//Create an optimized image 
		optimizedImage = SDL_DisplayFormat( loadedImage ); 
		//Free the old image 
		SDL_FreeSurface( loadedImage );
		//If the image was optimized just fine 
		if( optimizedImage != NULL ) { 
			//Map the color key 
			Uint32 colorkey = SDL_MapRGB( optimizedImage->format, 0xFF, 0xFF, 0xFF );
			//Set all pixels of color R 0, G 0xFF, B 0xFF to be transparent 
			SDL_SetColorKey( optimizedImage, SDL_SRCCOLORKEY, colorkey ); 
		}
	}
	else
	{
		optimizedImage = SDL_DisplayFormat( loadedImage );
		SDL_FreeSurface( loadedImage );
	}
	//Return the optimized image 
	return optimizedImage; 
} 


bool init_game(void)
{
	//Initialize all SDL subsystems 
	if( SDL_Init( SDL_INIT_EVERYTHING ) == -1 ) 
	{
		printf("init error\n"); 
		return false;
	}
	TTF_Init();
	screen = SDL_SetVideoMode(SCREEN_WIDTH, SCREEN_HEIGHT, SCREEN_BPP, SDL_SWSURFACE);
	//If there was an error in setting up the screen 
	if( screen == NULL ) 
	{ 
		printf("screen is NULL \n");
		return false;
	}
	//Set the window caption 
	SDL_WM_SetCaption( "Protect THE GREET WALL", NULL );
	return true;
}
bool load_data(void)
{
	/* 
		load all image	
	 */
	player.image = load_image("data/plane.gif", 1);
	if ( player.image == NULL ) {
		return false;
	}
	bullet.image = load_image("data/bullet.gif", 1);
	bullet.alive = 0;
	if ( bullet.image == NULL ) {
		return false;
	}
	enemy.image = load_image("data/enemy.gif", 1);
	enemy.alive = 0;
	if ( enemy.image == NULL ) {
		return false;
	}
	background = load_image("data/background.gif", 0);
	if ( background == NULL ) {
		return false;
	}
	
	font = TTF_OpenFont( "data/lazy.ttf", 25 );
	GAME_LEVEL = 1;
	final_score = 0;
	return true;
}

void apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination ) 
{ 	
	int i = 0;
	//Temporary rectangle to hold the offsets 
	SDL_Rect offset; 
	//Get the offsets 
	offset.x = x; 
	offset.y = y; 
	//Blit the surface 
	SDL_BlitSurface( source, NULL, destination, &offset ); 
	
}

void apply_background(void)
{
	int i;
	for ( i=0; i<screen->w; i += background->w ) {
		SDL_Rect dst;

		dst.x = i;
		dst.y = 0;
		dst.w = background->w;
		dst.h = background->h;
		SDL_BlitSurface(background, NULL, screen, &dst);
	}
}

void update_screen(void)
{
	SDL_UpdateRects(screen, 100, NULL);
}


void wait_frame(void){
	static Uint32 next_tick = 0;
	Uint32 this_tick;

	/* Wait for the next frame */
	this_tick = SDL_GetTicks(); 
	if ( this_tick < next_tick ) {
		SDL_Delay(next_tick-this_tick);
	}
	next_tick = this_tick + (1000/FRAMES_PER_SEC);
}


bool knock(Object o1, Object o2)
{
	if ( (o1.y >= (o2.y+o2.image->h)) ||
	     (o1.x >= (o2.x+o2.image->w)) ||
	     (o2.y >= (o1.y+o1.image->h)) ||
	     (o2.x >= (o1.x+o1.image->w)) ) {
		return false;
	}
	return true;
	     
}

void init_common_num(void)
{
	apear_enemy = 0;
	score = 0;
	shoot_time = 0;
	beat = 0;
	
}

void complete_level(SDL_Event event)
{
    player.facing = 0;	 
	if( event.type == SDL_KEYDOWN ) { 
		//Adjust the velocity 
		switch( event.key.keysym.sym ) { 
			case SDLK_n: 
				init_common_num(); 
				GAME_LEVEL ++;
				break; 
		} 
	}
	
}






