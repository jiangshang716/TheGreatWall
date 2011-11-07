#include "main.h"
#include "enemy.h"
void init_enemy(void)
{
	apear_enemy ++;
	if(apear_enemy > ENEMY_NUM )
	{
		enemy.x = -2000;
		enemy.y = -2000;
		return;
	}
	enemy.x = random() % SCREEN_WIDTH + 1;
	if( enemy.x > SCREEN_WIDTH - enemy.image->w)
	{
		enemy.x = SCREEN_WIDTH - enemy.image->w;
	}
	enemy.y = 0;
	enemy.facing = ENEMY_SPEED;
	enemy.alive = 1;
	enemy.image = (SDL_Surface*)load_image("data/enemy.gif", 1);
}

void enemy_move(void)
{
	
	if((random()%10) == 0){
		enemy.x -= enemy.facing * GAME_LEVEL; 
	}
	else if(random()%10 == 1)
	{
		enemy.x += enemy.facing * GAME_LEVEL; 
	}
	else if(random() % 10 == 2)
	{
		enemy.y += enemy.facing * GAME_LEVEL;
	}
//	enemy.y += enemy.facing;
	//If the dot went too far to the left or right 
	if(  enemy.x < 0 ) 
	{ 
		//move back 
		enemy.x += enemy.facing; 
		
	}
	else if( enemy.x + enemy.image->w > SCREEN_WIDTH  )
	{
		enemy.x -= enemy.facing; 
	}
	if( enemy.y > SCREEN_HEIGHT ) 
	{ 
		//move back
	//	printf("game over\n"); 
	//	exit(2);
		enemy.alive = 0;	
		
	}
}




void draw_enemy()
{
	SDL_Rect rctank;
	rctank.x = enemy.x;
	rctank.y = enemy.y;
//	printf("player.x=%d\n" , player.x);
//	printf("player.y=%d\n" , player.y);
	SDL_BlitSurface(enemy.image, NULL, screen, &rctank);

}


void clear_enemy(void)
{
	SDL_Rect rctank;
	rctank.x = enemy.x;
	rctank.y = enemy.y;
	SDL_BlitSurface(background, NULL, screen, &rctank);

}
