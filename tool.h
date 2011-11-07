#ifndef	TOOL_H
#define TOOL_H

SDL_Surface* 	load_image(char* filename , int formate);
bool 		init_game(void);
bool		load_data(void);
void 		apply_surface( int x, int y, SDL_Surface* source, SDL_Surface* destination );
void 		apply_background(void);
void		wait_frame(void);
void 		update_screen(void);
bool 		knock(Object o1, Object o2);
void 		init_common_num(void);
void 		complete_level(SDL_Event event);
#endif
