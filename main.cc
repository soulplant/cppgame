#include <iostream>
#include <sstream>
#include <SDL.h>
#include "utils.h"

using namespace std;

void DrawPixel(SDL_Surface *screen, int x, int y, Uint8 R, Uint8 G, Uint8 B) {
	Uint32 color = SDL_MapRGB(screen->format, R, G, B);

	if (SDL_MUSTLOCK(screen)) {
		if (SDL_LockSurface(screen) < 0) {
			cout << "Couldn't get lock." << endl;
			return;
		}
	}

    /*
	cout << "color = " << color << endl;
	Uint32 n = color;
	int bitsPerColor = screen->format->BytesPerPixel * 8 / 3;
	cout << "bitsPerColor " << bitsPerColor << endl;
	for (int i = 0; i < 3; i++) {
		cout << "[" << n % (2<<bitsPerColor) << "]";
	}
	cout << endl;
    */

	switch (screen->format->BytesPerPixel) {
		case 1: { /* Assuming 8-bpp */
			Uint8 *bufp;
			bufp = (Uint8 *)screen->pixels + y * screen->pitch + x;
			*bufp = color;
		}
		break;

		case 2: {
			Uint16 *bufp;
			bufp = (Uint16 *)screen->pixels + y*screen->pitch/2 + x;
			*bufp = color;
		}
		break;

		case 3: {
			Uint8 *bufp;
			bufp = (Uint8 *)screen->pixels + y*screen->pitch + x;
			*(bufp+screen->format->Rshift/8) = R;
			*(bufp+screen->format->Gshift/8) = G;
			*(bufp+screen->format->Bshift/8) = B;
		}
		break;

		case 4: {
			Uint32 *bufp;
			bufp = (Uint32 *)screen->pixels + y*screen->pitch/4 + x;
			*bufp = color;
		}
		break;
	}

	if (SDL_MUSTLOCK(screen)) {
		SDL_UnlockSurface(screen);
	}

	SDL_UpdateRect(screen, x, y, 1, 1);
}


int main(int argc, char** argv) {
	if (SDL_Init(SDL_INIT_AUDIO | SDL_INIT_VIDEO) < 0) {
		cout << "Unable to init SDL: " << SDL_GetError() << endl;
		return 1;
	}

	SDL_Surface *screen;
	screen = SDL_SetVideoMode(640, 480, 16, SDL_SWSURFACE);
	if (screen == NULL) {
		cout << "Unable to set 640x480 video: " << SDL_GetError() << endl;
		return 1;
	}
	atexit(SDL_Quit);

    cout << showByte(0xff) << endl;
    cout << showByte(0x0a) << endl;
    return 0;

	bool quit = false;
	SDL_Event event;
	while (!quit) {
		// Draw!
		DrawPixel(screen, 10, 10, 128, 4, 2);

		while (SDL_PollEvent(&event)) {
			switch (event.type) {
				case SDL_MOUSEMOTION:
					cout << "Mouse moved by " << event.motion.xrel << ", " << event.motion.yrel << endl;
					break;
				case SDL_MOUSEBUTTONDOWN:
					cout << "Mouse button " << event.button.button << " pressed at " << event.button.x << ", " << event.button.y << endl;
					break;
				case SDL_KEYDOWN:
				case SDL_QUIT:
					quit = true;
					break;
			}
		}
	}

	return 0;
}
