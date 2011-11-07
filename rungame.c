#include "main.h"
#include "rungame.h"
#include "tool.h"
#include "bullet.h"
#include "player.h"
#include "enemy.h"
int run()
{
	
	/* Initialize the random number generator */
	srand(time(NULL));
	bool quit = false;
	printf("running\n");
	
	if(!init_game())
	{
		exit(2);
	}
head:
	if(!load_data())
	{
		printf("data load error\n");
		exit(2);	
	}
	init_common_num();
	apply_background();
	init_player();
	draw_player();
	SDL_Color textColor = { 255, 255, 255 };
	//Update the screen 
	if( SDL_Flip( screen ) == -1 ) 
	{ 
		return 1; 
	}
	//While the user hasn't quit
	while( quit == false )
	{
//		printf("%d\n" , rand()%2);
		wait_frame();
		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{
			//If the user has Xed out the window
			if( event.type == SDL_QUIT )
			{
				quit = true;
			}
			
			if( apear_enemy > ENEMY_NUM)
			{
				complete_level(event);
			}
			else
			{		
				if( player.alive == 1)
				{
					player_input(event);				
				}	
				
			}
		}
		if(enemy.alive == 0)
		{
			init_enemy();
			
		}		
		if(enemy.alive == 1)
		{
			enemy_move();
		}

		if(bullet.alive == 1)
		{
			bullet_move();
		}

		if(knock(bullet , enemy)){
			enemy.image = load_image("data/boom.gif", 1);
			bullet.image = load_image("data/boom.gif", 1);
	//		draw_enemy();
	//		draw_bullet();
			enemy.alive = 0;
			bullet.alive = 0;
			bullet.x = -1000;
			bullet.y = -1000;
			score ++;
			final_score ++;
		}
		if(knock(player , enemy)){
			enemy.image = load_image("data/boom.gif", 1);
			player.image = load_image("data/boom.gif", 1);
	//		draw_enemy();
	//		draw_bullet();
			player.alive = 0;
			enemy.alive = 0;
			quit = true;
		}
		player_move();	
		apply_background();
		draw_enemy();

		if(bullet.alive == 1)
		{
			draw_bullet();
		}
		draw_player();
		if(apear_enemy > ENEMY_NUM)
		{
			
			char text0[256] = "";
			sprintf(text0, "      LEVEL   %d", GAME_LEVEL);
			message = TTF_RenderText_Solid( font, text0, textColor );
			apply_surface( 20 , 50 ,  message , screen);
			char text1[256] = "PRESS \"n\" TO NEXT LEVEL";
			message = TTF_RenderText_Solid( font, text1, textColor );
			apply_surface( 20 , 150 ,  message , screen);
			char text2[256] = "";
			sprintf(text2, "        SCORE:%d", score);
			message = TTF_RenderText_Solid( font, text2, textColor );
			apply_surface( 20 , 250 ,  message , screen);
			char text3[256] = "";
			
			if(score ==0 || shoot_time == 0)
			{
				sprintf(text3, "     ACCURATE:%d" , 0);
			}
			else
			{
				sprintf(text3, "     ACCURATE:%.2lf%%",(double)score/shoot_time*100);			
			}
			message = TTF_RenderText_Solid( font, text3, textColor );
			apply_surface( 20 , 350 ,  message , screen);
			
		}
		
		

		if( SDL_Flip( screen ) == -1 ) 
		{ 
			return 1; 
		}
		if(player.alive == 0){
			quit = true;
		}
		if(enemy.alive == 0)
		{
			init_enemy();
		}
		
		
	}

	char text1[256] = "       GAME  OVER   ";
	message = TTF_RenderText_Solid( font, text1, textColor );
	apply_surface( 20 , 50 ,  message , screen);
	char text2[256] = "";
	sprintf(text2, "       FINAL_SCORE:%d", final_score);
	message = TTF_RenderText_Solid( font, text2, textColor );
	apply_surface( 20 , 150 ,  message , screen);
	char text3[256] = "    PRESS \"r\" TO RESTART";
	message = TTF_RenderText_Solid( font, text3, textColor );
	apply_surface( 20 , 250 ,  message , screen);
	char text4[256] = "    PRESS \"q\" TO EXIT";
	message = TTF_RenderText_Solid( font, text4, textColor );
	apply_surface( 20 , 350 ,  message , screen);
	if( SDL_Flip( screen ) == -1 ) 
	{ 
		return 1; 
	}
	
	quit = false;
	while( quit == false )
	{
//		printf("%d\n" , rand()%2);
//		wait_frame();
		//While there's an event to handle
		while( SDL_PollEvent( &event ) )
		{
			//If the user has Xed out the window
			if( event.type == SDL_QUIT )
			{
				quit = true;
			}
			if( event.type == SDL_KEYDOWN ) { 
				//Adjust the velocity 
				switch( event.key.keysym.sym ) { 
					case SDLK_r: goto head; break; 
					case SDLK_q: quit = true; break; 
				}
			}
		}
	}
	
	//Close the font that was used 
	TTF_CloseFont( font ); 
	//Quit SDL_ttf 
	TTF_Quit(); 
	//Quit SDL 
	SDL_Quit(); 
}
