#include <SDL.h>
#include <stdbool.h>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;

void SDL_RenderDrawCircle(SDL_Renderer *renderer, int x, int y, int radius)
{
    for (int w = 0; w < radius * 2; w++) {
        for (int h = 0; h < radius * 2; h++) {
            int dx = radius - w; // horizontal distance to center
            int dy = radius - h; // vertical distance to center
            if ((dx*dx + dy*dy) <= (radius * radius)) {
                SDL_RenderDrawPoint(renderer, x + dx, y + dy);
            }
        }
    }
}

int main(int argc, char *argv[]) {
    // SDL inicializálása
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        SDL_Log("Nem sikerült az SDL inicializálása: %s", SDL_GetError());
        return 1;
    }

    // Ablak létrehozása
    SDL_Window *window = SDL_CreateWindow("Körök mozgatása", SDL_WINDOWPOS_UNDEFINED,
                                          SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
                                          SDL_WINDOW_SHOWN);
    if (window == NULL) {
        SDL_Log("Nem sikerült az ablak létrehozása: %s", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    // Renderer létrehozása
    SDL_Renderer *renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
    if (renderer == NULL) {
        SDL_Log("Nem sikerült a renderer létrehozása: %s", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    // Körök középpontjának és sugárának tárolása egy tömbben
    int circle_x[] = {100, 200, 300};
    int circle_y[] = {100, 200, 300};
    int circle_r = 50;

    // Ablak bezárásáig futó főciklus
    SDL_bool quit = SDL_FALSE;
    while (!quit) {
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            if (event.type == SDL_QUIT) {
                quit = SDL_TRUE;
            }
            // Az egérmozgatás eseményének kezelése
            if (event.type == SDL_MOUSEMOTION) {
                for (int i = 0; i < 3; i++) {
                    // Az egér koordinátáinak lekérdezése
                    int mouse_x, mouse_y;
                    SDL_GetMouseState(&mouse_x, &mouse_y);
                    // A kör középpontjának beállítása az egér pozíciójára
                    circle_x[i] = mouse_x;
                    circle_y[i] = mouse_y;
                }
            }
        }

        // Vászon törlése
        SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
        SDL_RenderClear(renderer);

        // Körök kirajzolása
        SDL_SetRenderDrawColor(renderer, 0, 0, 255, 255);
        for (int i = 0; i < 3; i++) {
            SDL_RenderDrawCircle(renderer, circle_x[i], circle_y[i], circle_r);
        }

        // Kirajzolás
        SDL_RenderPresent(renderer);
    }

    // Kilépés
    SDL_DestroyRenderer(renderer);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
