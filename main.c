#include <SDL3/SDL.h>

int main() {

  SDL_Init(SDL_INIT_VIDEO);

  SDL_Window *pwindow = SDL_CreateWindow("test", 900, 600, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  SDL_Rect left_paddle = {100, 300, 5, 45};
  SDL_Rect right_paddle = {800, 300, 5, 45};

  int move_down = 0;
  int move_up = 0;

  bool is_running = true;
  while (is_running) {

    SDL_FillSurfaceRect(psurface, NULL, 0x000000);
    SDL_FillSurfaceRect(psurface, &left_paddle, 0xFFFFFFF);
    SDL_FillSurfaceRect(psurface, &right_paddle, 0xFFFFFFF);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        is_running = false;
      }

      if (event.type == SDL_EVENT_KEY_DOWN) {

        switch (event.key.key) {
        case SDLK_DOWN:
          move_down = 1;
          break;
        case SDLK_UP:
          move_up = 1;
          break;
        }
      }

      if (event.type == SDL_EVENT_KEY_UP) {
        switch (event.key.key) {
        case SDLK_DOWN:
          move_down = 0;
          break;
        case SDLK_UP:
          move_up = 0;
          break;
        }
      }
    }

    if (move_down)
      left_paddle.y += 4;
    if (move_up)
      left_paddle.y -= 4;

    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(16);
  }

  SDL_DestroyWindow(pwindow);
  SDL_Quit();

  return 0;
}
