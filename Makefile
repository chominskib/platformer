thegame: anims.o bonuses.o entity.o env_constants.o events.o game.o hitbox.o main.o monsters.o platform.o render.o
	g++ main.o anims.o bonuses.o env_constants.o entity.o events.o game.o hitbox.o monsters.o platform.o render.o -o main -lsfml-graphics -lsfml-window -lsfml-system

anims.o: src/anims.cpp
	g++ -c src/anims.cpp

bonuses.o: src/bonuses.cpp
	g++ -c src/bonuses.cpp

entity.o: src/entity.cpp
	g++ -c src/entity.cpp

env_constants.o: src/env_constants.cpp
	g++ -c src/env_constants.cpp

events.o: src/events.cpp
	g++ -c src/events.cpp

game.o: src/game.cpp
	g++ -c src/game.cpp

hitbox.o: src/hitbox.cpp
	g++ -c src/hitbox.cpp

main.o: src/main.cpp
	g++ -c src/main.cpp

monsters.o: src/monsters.cpp
	g++ -c src/monsters.cpp

platform.o: src/platform.cpp
	g++ -c src/platform.cpp

render.o: src/render.cpp
	g++ -c src/render.cpp

.PHONY: clean

clean: 
	rm *.o main
