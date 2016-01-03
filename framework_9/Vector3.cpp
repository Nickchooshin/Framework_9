#include "Vector3.h"

namespace framework9
{
	// Vector2
	Vector2::Vector2()
		: x(0.0f), y(0.0f)
	{
	}
	Vector2::Vector2(const float &force)
		: x(0.0f), y(0.0f)
	{
	}
	Vector2::Vector2(const Vector2 &vector)
		: x(vector.x), y(vector.y)
	{
	}
	Vector2::Vector2(float X, float Y)
		: x(X), y(Y)
	{
	}

	Vector2& Vector2::operator +=(const Vector2 &vector)
	{
		x += vector.x;
		y += vector.y;

		return *this;
	}

	Vector2& Vector2::operator -=(const Vector2 &vector)
	{
		x -= vector.x;
		y -= vector.y;

		return *this;
	}

	Vector2& Vector2::operator *=(float scalar)
	{
		x *= scalar;
		y *= scalar;

		return *this;
	}

	Vector2& Vector2::operator /=(float scalar)
	{
		x /= scalar;
		y /= scalar;

		return *this;
	}

	Vector2 Vector2::operator +(const Vector2 &vector) const
	{
		Vector2 temp(*this);

		temp += vector;

		return temp;
	}

	Vector2 Vector2::operator -(const Vector2 &vector) const
	{
		Vector2 temp(*this);

		temp -= vector;

		return temp;
	}

	Vector2 Vector2::operator *(float scalar) const
	{
		Vector2 temp(*this);

		temp *= scalar;

		return temp;
	}

	Vector2 Vector2::operator /(float scalar) const
	{
		Vector2 temp(*this);

		temp /= scalar;

		return temp;
	}

	bool Vector2::operator ==(const Vector2 &vector) const
	{
		return (x == vector.x) && (y == vector.y);
	}

	bool Vector2::operator !=(const Vector2 &vector) const
	{
		return (x != vector.x) || (y != vector.y);
	}

	// Vector3
	Vector3::Vector3()
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}
	Vector3::Vector3(const float &force)
		: x(0.0f), y(0.0f), z(0.0f)
	{
	}
	Vector3::Vector3(const Vector3 &vector)
		: x(vector.x), y(vector.y), z(vector.z)
	{
	}
	Vector3::Vector3(float X, float Y, float Z)
		: x(X), y(Y), z(Z)
	{
	}

	Vector3& Vector3::operator +=(const Vector3 &vector)
	{
		x += vector.x;
		y += vector.y;
		z += vector.z;

		return *this;
	}

	Vector3& Vector3::operator -=(const Vector3 &vector)
	{
		x -= vector.x;
		y -= vector.y;
		z -= vector.z;

		return *this;
	}

	Vector3& Vector3::operator *=(float scalar)
	{
		x *= scalar;
		y *= scalar;
		z *= scalar;

		return *this;
	}

	Vector3& Vector3::operator /=(float scalar)
	{
		x /= scalar;
		y /= scalar;
		z /= scalar;

		return *this;
	}

	Vector3 Vector3::operator +(const Vector3 &vector) const
	{
		Vector3 temp(*this);

		temp += vector;

		return temp;
	}

	Vector3 Vector3::operator -(const Vector3 &vector) const
	{
		Vector3 temp(*this);

		temp -= vector;

		return temp;
	}

	Vector3 Vector3::operator *(float scalar) const
	{
		Vector3 temp(*this);

		temp *= scalar;

		return temp;
	}

	Vector3 Vector3::operator /(float scalar) const
	{
		Vector3 temp(*this);

		temp /= scalar;

		return temp;
	}

	bool Vector3::operator ==(const Vector3 &vector) const
	{
		return (x == vector.x) && (y == vector.y) && (z == vector.z);
	}

	bool Vector3::operator !=(const Vector3 &vector) const
	{
		return (x != vector.x) || (y != vector.y) || (z != vector.z);
	}
}