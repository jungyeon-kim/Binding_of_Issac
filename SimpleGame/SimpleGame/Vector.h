#pragma once

struct Vector
{
	float x{}, y{}, z{};

	const Vector& operator+(const Vector& rhs)
	{
		x += rhs.x;
		y += rhs.y;
		z += rhs.z;

		return *this;
	}
};