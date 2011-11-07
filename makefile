objects = main.o rungame.o tool.o bullet.o \
              enemy.o player.o

protect : $(objects)
	cc -o protect $(objects) -lSDL_image -lSDL_ttf -lSDL_mixer
main.o : main.h rungame.h
tool.o : main.h 
rungame.o : rungame.h main.h rungame.h tool.h bullet.h player.h enemy.h
bullet.o : bullet.h main.h
enemy.o : enemy.h main.h
player.o : player.h main.h

.PHONY : clean
clean :
	rm protect $(objects) 
