game: main.c
	gcc main.c data.c engine.c draw.c -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 -o game
