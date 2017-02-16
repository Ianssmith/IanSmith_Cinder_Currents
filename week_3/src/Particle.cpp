#include "../include/Particle.h"
#include "cinder/Rand.h"

Particle::Particle(glm::vec2 startPos, float size)
{
	cPos = startPos;
	rPos = cPos+ci::Rand::randGaussian()*10;
	//rPos = cPos+ci::Rand::randGaussian();
	//rPos = glm::vec2(cPos[0]+1, cPos[1]+1);
	velocity = glm::vec2(0.f, 0.75f);
	rspeed = glm::vec2(0.f, 0.f);

}
Particle::~Particle()
{
}

void Particle::update()
{
	cPos += velocity;
	rPos += cPos+ci::Rand::randGaussian();
	//rPos += glm::vec2(cPos[0]+ci::Rand::randGaussian()*1, cPos[1]+ci::Rand::randGaussian()*1);
	//multiply randGauss by "size" variable which should be passed in from instantiation[here it's one]
}

void Particle::draw()
{
	//ci::gl::pushModelView();
    // fancy color
    float value = ci::length(abs(velocity)) * 100.f;
    glm::clamp(value, 0.f, 1.f);
	//ci::gl::color(ci::Color(0.8f, 0.8f, 0.8f));
	//ci::gl::color(ci::Color(value, 0.f, 0.f));
    // draw cricle
    ci::gl::drawSolidCircle(cPos, 1.5f, 4);
    //ci::gl::drawLine(cPos, rPos);
	ci::gl::color(ci::Color(0.8f, 0.8f, 0.8f));
	//ci::gl::color(ci::Color(value, value/2, 0.f));
    ci::gl::drawLine(cPos, cPos + glm::vec2(10,10));

	//ci::gl::popModelView();
}

	



/*
Particle::Particle(glm::vec2 startPosition)
{
    // initialize variables
	position = startPosition;
	velocity = glm::vec2(0.f, 0.f);
	acceleration = glm::vec2(0.f, 0.f);
	friction = 0.95f;
}

Particle::~Particle()
{
}

void Particle::update()
{
    // add acc to vel
	velocity += acceleration;
    // apply friction
	velocity *= friction;
    // apply to positions
	position += velocity;
    // reset accelration
	acceleration *= 0.f;
}

void Particle::bounceForce(float damping, bool isVertical){
    // damping when hit corner
	if (isVertical){
		velocity.y = -velocity.y * damping;
	}
	else{
		velocity.x = -velocity.x * damping;
	}
}

void Particle::applyForce(glm::vec2 force)
{
    // apply force to acceleration
	acceleration += force;
}

void Particle::draw()
{
    // fancy color
    float value = ci::length(abs(velocity)) * 100.f;
    glm::clamp(value, 0.f, 1.f);
	ci::gl::color(ci::Color(value, 0.f, 0.7f));
    // draw cricle
    ci::gl::drawSolidCircle(position, 2.f, 4);
}
*/
