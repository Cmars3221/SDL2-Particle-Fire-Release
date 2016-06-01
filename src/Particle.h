/*
 * Particle.h
 *
 *  Created on: May 16, 2016
 *      Author: Aries
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

namespace pixelfire {

struct Particle {

	double m_x;
	double m_y;

//	 double m_xspeed ;
//	 double m_yspeed ;
	double m_speed;
	double m_direction;  // from 0-360 deg

public:

	Particle();
	virtual ~Particle();
	void update(int interval);        //update the position of the particle.

private:
	void init();

};

} /* namespace pixelfire */

#endif /* PARTICLE_H_ */
