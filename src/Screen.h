/*
 * Screen.h
 *
 *  Created on: May 11, 2016
 *      Author: Aries
 */

#ifndef SCREEN_H_
#define SCREEN_H_
#include "SDL.h"

namespace pixelfire {

class Screen {


public:

	const static int SCREEN_WIDTH = 800;
	const static int SCREEN_HEIGHT=  600;

private:
	SDL_Window *m_window;
	SDL_Renderer *m_renderer;
	SDL_Texture  *m_texture ;
	Uint32 *m_buffer1;
	Uint32 *m_buffer2;




public:

	Screen();
	bool init();
	bool processEvents();
	void close();
//	void clear();
	void update();
	void boxBlur();
	void setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue);
        //method for  taking xy coordinate then RGB with SDL type for consistency > Unsigned 8bit int.
    ~Screen();
};

} /* namespace pixelfire */

#endif /* SCREEN_H_ */
