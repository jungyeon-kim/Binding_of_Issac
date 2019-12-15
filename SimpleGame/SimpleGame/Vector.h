#pragma once

struct Vector
{
	float x{}, y{}, z{};

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
		return this->x == rhs.x && this->y == rhs.y && this->z == rhs.z;
	}
	bool operator!=(const Vector& rhs)
	{
		return this->x != rhs.x || this->y != rhs.y || this->z != rhs.z;
	}

	friend Vector operator-(Vector rhs)
	{
		rhs.x *= -1;
		rhs.y *= -1;
		rhs.z *= -1;

		return rhs;
	}
	friend Vector operator+(Vector lhs, const Vector& rhs)
	{
		lhs.x += rhs.x;
		lhs.y += rhs.y;
		lhs.z += rhs.z;

		return lhs;
	}
	friend Vector operator+(Vector lhs, float rhs)
	{
		lhs.x += rhs;
		lhs.y += rhs;
		lhs.z += rhs;

		return lhs;
	}
	friend Vector operator-(Vector lhs, const Vector& rhs)
	{
		lhs.x -= rhs.x;
		lhs.y -= rhs.y;
		lhs.z -= rhs.z;

		return lhs;
	}
	friend Vector operator-(Vector lhs, float rhs)
	{
		lhs.x -= rhs;
		lhs.y -= rhs;
		lhs.z -= rhs;

		return lhs;
	}
	friend Vector operator*(Vector lhs, const Vector& rhs)
	{
		lhs.x *= rhs.x;
		lhs.y *= rhs.y;
		lhs.z *= rhs.z;

		return lhs;
	}
	friend Vector operator*(Vector lhs, float rhs)
	{
		lhs.x *= rhs;
		lhs.y *= rhs;
		lhs.z *= rhs;

		return lhs;
	}
	friend Vector operator/(Vector lhs, const Vector& rhs)
	{
		lhs.x /= rhs.x;
		lhs.y /= rhs.y;
		lhs.z /= rhs.z;

		return lhs;
	}
	friend Vector operator/(Vector lhs, float rhs)
	{
		lhs.x /= rhs;
		lhs.y /= rhs;
		lhs.z /= rhs;

		return lhs;
	}
};