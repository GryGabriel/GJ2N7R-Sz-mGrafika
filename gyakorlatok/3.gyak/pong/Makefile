all:
	gcc -Iinclude/ src/ball.c src/game.c src/main.c src/pad.c src/pong.c -I/opt/homebrew/include/SDL2 -D_THREAD_SAFE -L/opt/homebrew/lib -lSDL2 -I/opt/homebrew/Cellar/glfw/include/ -L/opt/homebrew/Cellar/glfw/lib-arm64 -lglfw3 -framework Cocoa -framework OpenGL -framework IOKit -o pong -Wall -Wextra -Wpedantic

