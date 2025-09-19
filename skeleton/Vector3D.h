#pragma once

class Vector3D {

	double x, y, z;

public:
	Vector3D() : x(), y(), z() {};
	Vector3D(double a) : x(a), y(a), z(a) {};
	Vector3D(double a, double b, double c) : x(a), y(b), z(c) {};

	double mod() {
		// operaciones
	}

	Vector3D normalize() {
		//
	}


public:
	static Vector3D Vector3D::operator+(Vector3D& v1, Vector3D& v2) {
		return Vector3D(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z);
	}

	static Vector3D Vector3D::operator-(Vector3D& v1, Vector3D& v2) {
		return Vector3D(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z);
	}

	static bool Vector3D::operator==(Vector3D& v1, Vector3D& v2) {
		return v1.x == v2.x && v1.y == v2.y && v1.z == v2.z;
	}

	static Vector3D Vector3D::operator*(Vector3D& v, float a) {
		return Vector3D(v.x * a, v.y * a, v.z * a);
	}

	static double Vector3D::operator*(Vector3D& v1, Vector3D& v2) {
		return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
	}
};