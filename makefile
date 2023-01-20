compile:
	g++ --version
	g++ -std=c++20 -c src/main.cpp src/dino_behaviour.cpp src/ground_animation.cpp src/obstacle.cpp src/sftools/* -Iinclude
	g++ -std=c++20 main.o dino_behaviour.o load.o strman.o ground_animation.o obstacle.o -o app -lsfml-graphics -lsfml-window -lsfml-system 
	rm ./main.o ./load.o ./strman.o ./dino_behaviour.o ./ground_animation.o ./obstacle.o

run:
	./app