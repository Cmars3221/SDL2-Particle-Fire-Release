/*
 * Particle.cpp
 *
 *  Created on: May 16, 2016
 *      Author: Aries
 */

#include "Particle.h"
#include <stdlib.h>
#include <math.h>

namespace pixelfire {

Particle::Particle(): m_x(0), m_y(0) {   // starts from center.
	// TODO Auto-generated constructor stub
//	m_x = ((2.0 * rand())/RAND_MAX) -1;   // random value for particle movement
//	m_y = ((2.0 * rand())/RAND_MAX) -1;   // random value for particle movement

	  m_direction =  (2* M_PI *rand())/RAND_MAX; //angle
	  m_speed = (0.04 * rand())/RAND_MAX;

	  m_speed *= m_speed;

	  init();  //calling the init method from the constructor.

}

 void Particle::init(){
	  m_x = 0;
	  m_y = 0;
	  m_direction =  (2* M_PI *rand())/RAND_MAX; //angle
	  m_speed = (0.04 * rand())/RAND_MAX;

	  m_speed *= m_speed;
 }

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}


void Particle::update(int interval){

	m_direction += interval*0.0003; // gives the particles a curl.

	double xspeed = m_speed * cos(m_direction);

	double yspeed = m_speed * sin(m_direction);

	m_x += xspeed * interval;
	m_y += yspeed * interval;

	if(m_x < -1 || m_x > 1 || m_y < -1 || m_y >1 ){
			init();

	}

	   if(rand() < RAND_MAX/100){
		   init();
	   }


}



} /* namespace pixelfire */
