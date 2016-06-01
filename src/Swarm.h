/*
 * Swarm.h
 *
 *  Created on: May 16, 2016
 *      Author: Aries
 */

#ifndef SWARM_H_
#define SWARM_H_

#include "Particle.h"

namespace pixelfire {

class Swarm {

public:
	 const static int NPARTICLES = 6000;  // your particle count.
private:
 Particle * m_pParticles;
 int lastTime;

public:
	Swarm();
	virtual ~Swarm();
	void update(int elapsed);

	const Particle * const getParticles(){return m_pParticles;};
};

} /* namespace pixelfire */

#endif /* SWARM_H_ */
