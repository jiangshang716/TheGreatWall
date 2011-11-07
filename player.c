#include "player.h"
#include "main.h"
void init_player()
{
	player.x = SCREEN_WIDTH/2 - player.image->w/2;
	player.y = SCREEN_HEIGHT - player.image->h;
	player.facing = 0;
	player.alive = 1;

}

void player_move()
{
	
	//Move the dot left or right 
	player.x += player.facing; 
	//If the dot went too far to the left or right 
	if( ( player.x < 0 ) || ( player.x + player.image->w > SCREEN_WIDTH ) ) 
	{ 
		//move back 
		player.x -= player.facing; 

	}

}

void draw_player()
{
	SDL_Rect rctank;
	rctank.x = player.x;
	rctank.y = player.y;
//	printf("player.x=%d\n" , player.x);
//	printf("player.y=%d\n" , player.y);
	SDL_BlitSurface(player.image, NULL, screen, &rctank);

}


void clear_player(void)
{
	SDL_Rect rctank;
	rctank.x = player.x;
	rctank.y = player.y;
	SDL_BlitSurface(background, NULL, screen, &rctank);

}


void player_input(SDL_Event event)
{
	if( event.type == SDL_KEYDOWN ) { 
		//Adjust the velocity 
		switch( event.key.keysym.sym ) { 
			case SDLK_LEFT: player.facing -= 2; break; 
			case SDLK_RIGHT: player.facing += 2; break; 
			case SDLK_a: player.facing -= 2; break; 
			case SDLK_d: player.facing += 2; break; 
			case SDLK_SPACE: 
//					printf("space down\n\n\n\n\n\n\n\n\n\n\n\n\n"); 
					
					if(bullet.alive == 0){
						init_bullet() ;
						bullet.facing += 8; 
						shoot_time ++;
					}
					break;
		} 
	}
	//If a key was released 
	else if( event.type == SDL_KEYUP ) 
	{ 
		//Adjust the velocity 
		switch( event.key.keysym.sym ) { 
			case SDLK_LEFT: player.facing += 2; break; 
			case SDLK_RIGHT: player.facing -= 2; break; 
			case SDLK_a: player.facing += 2; break; 
			case SDLK_d: player.facing -= 2; break; 
//			case SDLK_SPACE:   printf("space up\n\n\n\n\n\n\n\n\n\n\n\n"); break;
		} 
	}
}
