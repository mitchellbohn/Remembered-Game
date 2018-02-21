#ifndef ANIMATION_HPP
#define ANIMATION_HPP

class Animation {
	SDL_Texture *texture;
	Window *win;
	int w, h, time;
	bool done;
public:
	int getTime() { return time; }
	void render(Window *win, int x, int y) {
		SDL_Rect src, dest;
		src.x=(int)0; src.y=(int)0; src.w=w; src.h=h;
		dest.x=(int)x; dest.y=(int)y; dest.w=w; dest.h=h;
		SDL_RenderCopy(win->getRenderer(), texture, &src, &dest);
	}
	void setup(Window *newWin, string file, int newTime) {
		done = false;
		win = newWin;
		time = newTime;
		SDL_Surface *image=SDL_LoadBMP(file.c_str());
		if (image == NULL) {
			cout << "Could not create image:\n" << SDL_GetError() << endl;
			done = true;
			return;
		}
		SDL_SetColorKey(image, SDL_TRUE, SDL_MapRGB(image->format, 0, 0, 255));
		texture=SDL_CreateTextureFromSurface(win->getRenderer(), image);
		if (texture == NULL) {
			cout << "Could not create texture:\n" << SDL_GetError() << endl;
			done = true;
			return;
		}
		SDL_FreeSurface(image);
		SDL_QueryTexture(texture, NULL, NULL, &w, &h);
	}
	void cleanup(){ SDL_DestroyTexture(texture); }
};
#endif
