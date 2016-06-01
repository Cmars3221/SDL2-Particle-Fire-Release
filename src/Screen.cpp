/*
 * Screen.cpp
 *
 *  Created on: May 11, 2016
 *      Author: Aries
 */

#include "Screen.h"

namespace pixelfire {

Screen::Screen() :
		m_window(NULL), m_renderer(NULL), m_texture(NULL), m_buffer1 (NULL), m_buffer2(NULL) {

}

Screen::~Screen() {
	// TODO Auto-generated destructor stub
}

bool Screen::init() {

	if (SDL_Init(SDL_INIT_VIDEO) < 0) {

//		cout << "SDL init failed"<<endl;
		return false;
	}

	//removing the SDL object definition.
	m_window = SDL_CreateWindow("Fire Explosion", SDL_WINDOWPOS_UNDEFINED,
			SDL_WINDOWPOS_UNDEFINED, SCREEN_WIDTH, SCREEN_HEIGHT,
			SDL_WINDOW_SHOWN);

	if (m_window == NULL) {
		SDL_Quit();
//			cout<<"Error opening window"<<endl;
		return false;
	}

	m_renderer = SDL_CreateRenderer(m_window, -1, SDL_RENDERER_PRESENTVSYNC);
	m_texture = SDL_CreateTexture(m_renderer, SDL_PIXELFORMAT_RGBA8888,
			SDL_TEXTUREACCESS_STATIC, SCREEN_WIDTH, SCREEN_HEIGHT);

	if (m_renderer == NULL) {
//			   cout<<"Could not create renderer"<<endl;
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;

	}

	if (m_texture == NULL) {
//			   cout<< "Could not create texture" <<endl;
		SDL_DestroyRenderer(m_renderer);
		SDL_DestroyWindow(m_window);
		SDL_Quit();
		return false;
	}

	m_buffer1 = new Uint32[SCREEN_WIDTH *SCREEN_HEIGHT]; // allocating the actual buffer.
	m_buffer2 = new Uint32[SCREEN_WIDTH *SCREEN_HEIGHT];

//	Uint32 *buffer = new Uint32[SCREEN_WIDTH * SCREEN_HEIGHT]; //here's our buffer being set to the viewport's width and size. Make note of the Uint32 object being set as the buffer medium.

	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32)); // maximizing all we can with the buffer // clearing the buffer.
	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//		   	buffer[60000] = 0xFFFF00FF;   //individual pixel manipulation.

//	for (int i = 0; i < SCREEN_WIDTH * SCREEN_HEIGHT; i++) {
//		buffer[i] = 0xFFFF00FF;
//	} //and here we manipulate the entire view-port.  RGBA equate to 4bytes or 32bits each byte is 2 decimal number spaces.



	return true;

}

void Screen::boxBlur(){  //create a whole new screen of pixel then draw that screen.
 //swapping the buffers..
	Uint32 *holder = m_buffer1;
	 m_buffer1 = m_buffer2;
	 m_buffer2 = holder;

	 for (int y = 0; y<SCREEN_HEIGHT; y++){
		 for (int x = 0; x<SCREEN_WIDTH; x++){


			 int redTotal = 0;
			 int greenTotal =0;
			 int blueTotal= 0;

			 for(int row=-1; row <=1; row++){
				 for(int col=-1; col<=1; col++){
					 int currentX =  x + col;
					 int currentY = y +row;

					 if(currentX >= 0 && currentX < SCREEN_WIDTH && currentY >=0 && currentY < SCREEN_HEIGHT){
						Uint32 color = m_buffer2[currentY*SCREEN_WIDTH + currentX];

						Uint8 red  = color >> 24;
						Uint8 green= color >> 16;
						Uint8 blue = color >>8;

						redTotal += red;
						greenTotal +=green;
						blueTotal +=blue;
					 }

				 }
			 }

			  	  Uint8 red = redTotal/9;
			  	  Uint8 green = greenTotal/9;
			  	  Uint8 blue =blueTotal/9;

			  	  setPixel(x,y,red,green,blue);
		 }
	 }






}

//void Screen::clear(){
//	memset(m_buffer1, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//	memset(m_buffer2, 0, SCREEN_WIDTH * SCREEN_HEIGHT * sizeof(Uint32));
//}

void Screen::setPixel(int x, int y, Uint8 red, Uint8 green, Uint8 blue){

	  if (x < 0 || x>= SCREEN_WIDTH || y<0 || y >= SCREEN_HEIGHT){
		   return;
	  }
	  Uint32 color = 0;

	  color += red;  // bit shifting start with red..then sequentially shift it by 1 byte.
	  color <<= 8;
	  color += green;
	  color <<=8;
	  color += blue;
	  color <<= 8;
	  color += 0xFF; // alpha value, No val.   End result  RGBA..
	   //red is shifted 8 bits to the left...so on so forth.



	  m_buffer1[(y * SCREEN_WIDTH) + x ] = color;  //going down a row and
 // so to get right pixel we multiply y by screen width..
	   // ex 10 rows... with 10 rows, each row has the screen width.  then we add x or (column value).
// remember the buffer represents all pixels!
}


void Screen::update(){
	SDL_UpdateTexture(m_texture, NULL, m_buffer1, SCREEN_WIDTH * sizeof(Uint32));
	SDL_RenderClear(m_renderer);
	SDL_RenderCopy(m_renderer, m_texture, NULL, NULL);
	SDL_RenderPresent(m_renderer);
}

//here we're setting up and SDL event queue.  Event: Mouse click, key up down, or Clicking the window's close button in this case.
bool Screen::processEvents() {
	SDL_Event event;  //declaration outside of the loop for recreation.
	while (SDL_PollEvent(&event)) {

		if (event.type == SDL_QUIT) {  //the event we're checking for.
			return false;

		}
	}

	return true;

}
void Screen::close() {

	delete[] m_buffer1;
	delete[] m_buffer2;
	SDL_DestroyRenderer(m_renderer);
	SDL_DestroyTexture(m_texture);
	SDL_DestroyWindow(m_window);
	SDL_Quit();
}

} /* namespace pixelfire */
