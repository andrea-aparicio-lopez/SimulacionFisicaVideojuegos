#include "Vector3D.h"
#include <math.h>

Vector3D::Vector3D() : x(), y(), z() {};
Vector3D::Vector3D(float a) : x(a), y(a), z(a) {};
Vector3D::Vector3D(float a, float b, float c) : x(a), y(b), z(c) {};

float Vector3D::modulo() const {
	return sqrt(pow(x, 2) + pow(y, 2) + pow(z, 2));
}

void Vector3D::normalize() {
	float mod = modulo();
	x /= mod;
	y /= mod;
	z /= mod;
}