#include <iostream>
#include <SDL.h>
#include <SDL_opengl.h>

using namespace std;

void Draw() {
  glClear(GL_COLOR_BUFFER_BIT);
  glBegin(GL_TRIANGLES);
  glColor3f(1, 0, 0);
  glVertex2f(0.0, 0.0);
  glColor3f(0, 1, 0);
  glVertex2f(0.0, 100.0);
  glColor3f(0, 0, 1);
  glVertex2f(100, 100);
  glEnd();
}

int main(int argc, char** argv) {
  if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO | SDL_INIT_EVERYTHING) < 0) {
    cout << "Unable to init SDL: " << SDL_GetError() << endl;
    return 1;
  }

  SDL_GL_SetAttribute(SDL_GL_RED_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE, 8);
  SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

  SDL_Surface *screen;
  screen = SDL_SetVideoMode(640, 480, 0, SDL_OPENGL);
  if (screen == NULL) {
    cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
    return 1;
  }
  atexit(SDL_Quit);

  glViewport(0, 0, screen->w, screen->h);
  glOrtho(0.0,
				  (GLdouble) screen->w, (GLdouble) screen->h,
				  0.0,        // top edge
				  0.0, 1.0);  // near and far clipping planes

  glClearColor(0, 0, 0, 0);

  SDL_WM_SetCaption("title", "str2");

  bool quit = false;
  SDL_Event event;
  while (!quit) {
    while (SDL_PollEvent(&event)) {
      switch (event.type) {
        case SDL_MOUSEMOTION:
          cout << "Mouse moved by " << event.motion.xrel << ", " << event.motion.yrel << endl;
          cout << "Mouse at " << event.motion.x << ", " << event.motion.y << endl;
          break;
        case SDL_MOUSEBUTTONDOWN:
          cout << "Mouse button " << event.button.button << " pressed at " << event.button.x << ", " << event.button.y << endl;
          break;
        case SDL_KEYDOWN:
          if (event.key.keysym.sym == SDLK_q) {
            quit = true;
          }
          break;
        case SDL_QUIT:
          quit = true;
          break;
      }
    }
    Draw();
    SDL_GL_SwapBuffers();
  }

  return 0;
}
