all:
	gcc visualizer.c -o visualizer -lraylib -lGL -lm -lpthread -ldl -lrt -lX11
run:
	gcc visualizer.c -o visualizer -lraylib -lGL -lm -lpthread -ldl -lrt -lX11 && ./visualizer
