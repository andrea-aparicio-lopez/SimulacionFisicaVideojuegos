#include "Particle.h"

#include "iostream"

using namespace physx;

Particle::Particle(PxVec3 pos, PxVec3 vel, PxVec3 a, PxVec4 color, double ltime, double damping, uint8_t mode)
	: _tr(new PxTransform(pos))
	, _prevPos(_tr->p)
	, _vel(vel) 
	, _accel(a)
	, _color(color)

	, _lifetime(ltime)
	, _alive(true)

	, _damping(damping)
	, _integrMode(mode)
{
	// Inicializar RenderItem
	PxSphereGeometry geo = PxSphereGeometry(1.0f);
	auto shape = CreateShape(geo);
	_renderItem = new RenderItem(shape, _tr, _color);
	RegisterRenderItem(_renderItem);
}

Particle::Particle(Particle* const& other) 
	: _tr(new PxTransform(other->_tr->p))
	, _prevPos(_tr->p)
	, _vel(other->_vel)
	, _accel(other->_accel)
	, _color(other->_color)

	, _lifetime(other->_lifetime)
	, _alive(true)

	, _damping(other->_damping)
	, _integrMode(other->_integrMode)
{
	// Inicializar RenderItem
	PxSphereGeometry geo = PxSphereGeometry(1.0f);
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
	switch (_integrMode)
	{
	case integrateMode::EULER:
		_prevPos = _tr->p;
		_tr->p += dt * _vel;
		_vel += dt * _accel;
		_vel *= pow(_damping, dt);
		break;

	case integrateMode::VERLET: {
		auto const currPos = _tr->p;
		_tr->p = 2 * _tr->p - _prevPos + pow(dt, 2) * _accel;
		_prevPos = currPos;
		break;
	}
	case integrateMode::EULER_SEMIIMPLICIT:
	default:
		_prevPos = _tr->p;
		_vel += dt * _accel;
		_tr->p += dt * _vel;
		_vel *= pow(_damping, dt);
		break;
	}

	_lifetime -= dt;
	_alive = _lifetime > 0.;
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

void Particle::setLifetime(double lifetime) {
	_lifetime = lifetime;
}

bool Particle::isAlive() const {
	return _alive;
}