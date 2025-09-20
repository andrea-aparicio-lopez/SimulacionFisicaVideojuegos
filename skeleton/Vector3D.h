#pragma once

class Vector3D {
public:

	float x, y, z;

	Vector3D();
	Vector3D(float a);
	Vector3D(float a, float b, float c);

	float modulo() const;
	void normalize();


public:
	inline Vector3D operator+(const Vector3D& other) {
		return Vector3D(x + other.x, y + other.y, z + other.z);
	}

	inline Vector3D operator-(const Vector3D& other) {
		return Vector3D(x - other.x, y - other.y, z - other.z);
	}

	inline bool operator==(const Vector3D& other) {
		return x == other.x && y == other.y && z == other.z;
	}

	inline Vector3D operator*(const float& a) {
		return Vector3D(x * a, y * a, z * a);
	}

	inline float operator*(const Vector3D& other) {
		return (x * other.x + y * other.y + z * other.z);
	}
};