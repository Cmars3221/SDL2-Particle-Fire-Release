/*
 * Swarm.cpp
 *
 *  Created on: May 16, 2016
 *      Author: Aries
 */

#include "Swarm.h"

namespace pixelfire {

Swarm::Swarm(): lastTime(0) {

	m_pParticles = new Particle[NPARTICLES];
	// TODO Auto-generated constructor stub

}

Swarm::~Swarm() {

	delete [] m_pParticles;
	// TODO Auto-generated destructor stub
}

void Swarm::update(int elapsed){

	int interval = elapsed - lastTime;

	for(int i=0; i<Swarm::NPARTICLES; i++){
		m_pParticles[i].update(interval);

		lastTime = elapsed;
	}


}

} /* namespace pixelfire */
