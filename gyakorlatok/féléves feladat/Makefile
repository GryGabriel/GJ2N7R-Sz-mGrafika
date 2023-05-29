all:
	gcc -Iinclude/ src/app.c src/camera.c src/main.c src/scene.c src/texture.c src/utils.c src/load.c src/draw.c src/model.c -I/opt/homebrew/include/SDL2 -lSDL2 -lSDL2_image -D_THREAD_SAFE -L/opt/homebrew/lib -I/opt/homebrew/Cellar/glfw/include/ -L/opt/homebrew/Cellar/glfw  -lm -framework Cocoa -framework OpenGL -framework IOKit -o program -Wall -Wextra -Wpedantic
