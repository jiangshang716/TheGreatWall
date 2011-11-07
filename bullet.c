
#include "bullet.h"
#include "main.h"
void bullet_move()
{
	
	//Move the dot left or right 
	bullet.y -= bullet.facing; 
	//If the dot went too far to the left or right 
	if( ( bullet.y < 0 ) ) 
	{ 
		//move back 
		bullet.facing = 0; 
		bullet.alive = 0;
	}

}



void init_bullet(void)
{
	bullet.x = player.x + (player.image->w)/2;
	bullet.y = SCREEN_HEIGHT - player.image->h;
//	printf("current player x = %d\n", player.x);
//	printf("init bullet x = %d\n" , bullet.x);
	bullet.facing = 3;
	bullet.alive = 1;
	bullet.image = load_image("data/bullet.gif", 1);
}


void draw_bullet(void)
{
	SDL_Rect rctank;
	rctank.x = bullet.x;
	rctank.y = bullet.y;
//	printf("bullet.x=%d\n" , bullet.x);
//	printf("bullet.y=%d\n" , bullet.y);
	SDL_BlitSurface(bullet.image, NULL, screen, &rctank);

}


void clear_bullet(void)
{
	SDL_Rect rctank;
	rctank.x = bullet.x;
	rctank.y = bullet.y;
	SDL_BlitSurface(background, NULL, screen, &rctank);

}
