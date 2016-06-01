//============================================================================
// Name        : SDL.cpp
// Author      : Chris
// Version     :
// Copyright   :
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <SDL.h>
#include <math.h>
#include "Screen.h"
#include <time.h>
#include "Swarm.h"
using namespace std;
using namespace pixelfire;


int main() {

	srand(time(NULL));

	   Screen screen;

	    if (screen.init()== false){
	    	cout <<" Error Initializing SDL." <<endl;
	    }


	    Swarm swarm;      //creates the object

	    while (true){

	    	const Particle * const pParticles = swarm.getParticles();

	    	int elapsed = SDL_GetTicks();




	    	swarm.update(elapsed);

	    	unsigned char green = (unsigned char)(1+ sin(elapsed *0.0001)) * 128;
	    	unsigned char red = (unsigned char)(1+ sin(elapsed *0.0002)) * 128;
	    	unsigned char blue = (unsigned char)(1+ sin(elapsed *0.0003)) * 128;




	    	for(int i=0; i<Swarm::NPARTICLES; i++){
	    		Particle particle = pParticles[i];

	    		int x = (particle.m_x + 1) * Screen::SCREEN_WIDTH/2;  // so it's positive.
	    	    int y = particle.m_y * Screen::SCREEN_WIDTH/2 + Screen::SCREEN_HEIGHT/2; //  extending the range of the particle. and positioning it in the middle of the screen.

	    	    screen.setPixel(x,y, red, green, blue);
	    	}


//	    	for(int y=0; y < Screen::SCREEN_HEIGHT; y++){
//	    		for(int x=0; x < Screen::SCREEN_WIDTH; x++){
//	    			screen.setPixel(x, y, red, green, blue);
//	    		}
//	    	}

	    	screen.boxBlur();

			screen.update();  // after pixel colors are set we update.



			 if(screen.processEvents() == false){
				 break;                              //if a false value is returned from the event loop, then it will
		 	 	 	 	 	 	 //activate the break procedure here, and the game loop ends..game ends.

			 }
		}


	screen.close();                      //and if the game loop ends we initiate the destroy procedure.

	return 0;
}
