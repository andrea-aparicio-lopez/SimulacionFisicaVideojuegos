#include "Particle.h"

#include "iostream"

using namespace physx;

Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 a, PxVec4 color, float size, double mass,
	double ltime, double dist, double damping, uint8_t mode)
	: _tr(new PxTransform(pos))
	, _prevPos(_tr->p)
	, _vel(vel) 
	, _accel(a)
	, _color(color)
	, _size(size)

	, _lifetime(ltime)
	, _distance(dist)
	, _alive(true)

	, _damping(damping)
	, _integrMode(mode)

	, _mass(mass)
	, _force({0,0,0})
{
	// Inicializar RenderItem
	PxSphereGeometry geo = PxSphereGeometry(_size);
	auto shape = CreateShape(geo);
	_renderItem = new RenderItem(shape, _tr, _color);
}

Particle::Particle(Particle* const& other) 
	: _tr(new PxTransform(other->_tr->p))
	, _prevPos(_tr->p)
	, _vel(other->_vel)
	, _accel(other->_accel)
	, _color(other->_color)
	, _size(other->_size)

	, _lifetime(other->_lifetime)
	, _distance(other->_distance)
	, _alive(true)

	, _damping(other->_damping)
	, _integrMode(other->_integrMode)
{
	// Inicializar RenderItem
	PxSphereGeometry geo = PxSphereGeometry(_size);
	auto shape = CreateShape(geo);
	_renderItem = new RenderItem(shape, _tr, _color);
	RegisterRenderItem(_renderItem);
}

Particle::~Particle() {
	_renderItem->release();
	DeregisterRenderItem(_renderItem);
	delete _tr;
}

void Particle::integrate(double dt) {
	auto a = _accel + (_force / _mass);

	switch (_integrMode)
	{
	case integrateMode::EULER:
		_prevPos = _tr->p;
		_tr->p += dt * _vel;
		_vel += dt * a;
		_vel *= pow(_damping, dt);
		break;

	case integrateMode::VERLET: {
		auto const currPos = _tr->p;
		_tr->p = 2 * _tr->p - _prevPos + pow(dt, 2) * a;
		_prevPos = currPos;
		break;
	}
	case integrateMode::EULER_SEMIIMPLICIT:
	default:
		_prevPos = _tr->p;
		_vel += dt * a;
		_tr->p += dt * _vel;
		_vel *= pow(_damping, dt);
		break;
	}

	_lifetime -= dt;
	_distance -= (_tr->p - _prevPos).magnitude();
	_alive = _lifetime > 0. && _distance > 0.;
}

physx::PxVec3 Particle::getPos() const {
	return _tr->p;
}
void Particle::setPos(physx::PxVec3 pos) {
	_tr->p = pos;
	_prevPos = pos;
}

physx::PxVec3 Particle::getVel() const {
	return _vel;
}
void Particle::setVel(physx::PxVec3 vel) {
	_vel = vel;
}

physx::PxVec3 Particle::getAccel() const {
	return _accel;
}
void Particle::setAccel(physx::PxVec3 a) {
	_accel = a;
}

physx::PxVec4 Particle::getColor() const {
	return _color;
}
void Particle::setColor(physx::PxVec4 color) {
	_color = color;
	_renderItem->color = color;
}

void Particle::setSize(float size) {
	_size = size;
}

double Particle::getLifetime() const {
	return _lifetime;
}

void Particle::setLifetime(double lifetime) {
	_lifetime = lifetime;
}

void Particle::setDistance(double dist) {
	_distance = dist;
}

bool Particle::isAlive() const {
	return _alive;
}

void Particle::addForce(PxVec3 force) {
	_force += force;
}

void Particle::clearForce() {
	_force = { 0,0,0 };
}
