#include <SDL3/SDL.h>

#define WINDOW_LENGTH 900
#define WINDOW_WIDTH 600
#define PADDLE_HEIGHT 45
#define PADDLE_WIDTH 5
#define BALL_SIZE 6

bool collide(SDL_Rect a, SDL_Rect b);

int main() {

  SDL_Init(SDL_INIT_VIDEO);
  SDL_Window *pwindow =
      SDL_CreateWindow("test", WINDOW_LENGTH, WINDOW_WIDTH, 0);
  SDL_Surface *psurface = SDL_GetWindowSurface(pwindow);

  int left_paddle_x = 100;
  int left_paddle_y = 300;
  int right_paddle_x = 800;
  int right_paddle_y = 300;

  SDL_Rect left_paddle = {left_paddle_x, left_paddle_y, PADDLE_WIDTH,
                          PADDLE_HEIGHT};

  SDL_Rect right_paddle = {right_paddle_x, right_paddle_y, PADDLE_WIDTH,
                           PADDLE_HEIGHT};
  SDL_Rect ball = {WINDOW_LENGTH / 2, WINDOW_WIDTH / 2, BALL_SIZE, BALL_SIZE};

  bool move_down = false;
  bool move_up = false;

  int ball_x_vel = 3;
  int ball_y_vel = 3;

  bool is_running = true;
  while (is_running) {

    SDL_FillSurfaceRect(psurface, NULL, 0x000000);
    SDL_FillSurfaceRect(psurface, &left_paddle, 0xFFFFFFF);
    SDL_FillSurfaceRect(psurface, &right_paddle, 0xFFFFFFF);
    SDL_FillSurfaceRect(psurface, &ball, 0xFFFFFFF);

    SDL_Event event;
    while (SDL_PollEvent(&event)) {
      if (event.type == SDL_EVENT_QUIT) {
        is_running = false;
      }

      if (event.type == SDL_EVENT_KEY_DOWN) {

        switch (event.key.key) {
        case SDLK_DOWN:
          move_down = true;
          break;
        case SDLK_UP:
          move_up = true;
          break;
        }
      }

      if (event.type == SDL_EVENT_KEY_UP) {
        switch (event.key.key) {
        case SDLK_DOWN:
          move_down = false;
          break;
        case SDLK_UP:
          move_up = false;
          break;
        }
      }
    }

    if (collide(ball, left_paddle)) {
      ball_x_vel *= -1;
    }

    ball.x += ball_x_vel;
    ball.y += ball_y_vel;

    if (ball.x >= 900 || ball.x <= 0) {
      ball_x_vel *= -1;
    }

    if (ball.y >= 600 || ball.y <= 0) {
      ball_y_vel *= -1;
    }

    if (ball.y <= (left_paddle_y + PADDLE_HEIGHT) && ball.y >= left_paddle_y) {
      ball_x_vel *= -1;
    }

    if (move_down)
      left_paddle.y += 6;
    if (move_up)
      left_paddle.y -= 6;

    SDL_UpdateWindowSurface(pwindow);
    SDL_Delay(16);
  }

  SDL_DestroyWindow(pwindow);
  SDL_Quit();

  return 0;
}

bool collide(SDL_Rect a, SDL_Rect b) {
  return a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h &&
         a.y + a.h > b.y;
}
