#pragma once

struct Vector
{
	float x{}, y{}, z{};

	Vector operator+(const Vector& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}
	Vector operator-(const Vector& rhs)
	{
		x -= rhs.x;
		y -= rhs.y;
		z -= rhs.z;

		return *this;
	}
	Vector operator*(const Vector& rhs)
	{
		x *= rhs.x;
		y *= rhs.y;
		z *= rhs.z;

		return *this;
	}
	Vector operator*(float rhs)
	{
		x *= rhs;
		y *= rhs;
		z *= rhs;

		return *this;
	}
	Vector operator/(float rhs)
	{
		x /= rhs;
		y /= rhs;
		z /= rhs;

		return *this;
	}
	bool operator<(const Vector& rhs)
	{
		return this->x < rhs.x || this->y < rhs.y || this->z < rhs.z;
	}
	bool operator>(const Vector& rhs)
	{
		return this->x > rhs.x || this->y > rhs.y || this->z > rhs.z;
	}
	bool operator==(const Vector& rhs)
	{
		return this->x == rhs.x || this->y == rhs.y || this->z == rhs.z;
	}
};