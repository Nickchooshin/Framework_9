#include "Vector.h"

#include <math.h>

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

	Vector2 Vector2::operator + () const
	{
		Vector2 temp(*this);

		return temp;
	}

	Vector2 Vector2::operator - () const
	{
		Vector2 temp(*this);

		temp.x = -temp.x;
		temp.y = -temp.y;

		return temp;
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

	float Vector2::Dot(const Vector2 &vector1, const Vector2 &vector2)
	{
		float temp = (vector1.x * vector2.x) + (vector1.y * vector2.y);

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

	Vector2 Vector2::Normalize() const
	{
		Vector2 temp(*this);

		float lengthSq = (x * x) + (y * y);
		float length = sqrtf(lengthSq);

		temp /= length;

		return temp;
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

	Vector3 Vector3::operator + () const
	{
		Vector3 temp(*this);

		return temp;
	}

	Vector3 Vector3::operator - () const
	{
		Vector3 temp(*this);

		temp.x = -temp.x;
		temp.y = -temp.y;
		temp.z = -temp.z;

		return temp;
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

	Vector3 Vector3::Normalize() const
	{
		Vector3 temp(*this);

		float lengthSq = (x * x) + (y * y) + (z * z);
		float length = sqrtf(lengthSq);

		temp /= length;

		return temp;
	}

	Vector3 Vector3::Cross(const Vector3 &vector1, const Vector3 &vector2)
	{
		Vector3 temp;

		temp.x = (vector1.y * vector2.z) - (vector1.z * vector2.y);
		temp.y = (vector1.z * vector2.x) - (vector1.x * vector2.z);
		temp.z = (vector1.x * vector2.y) - (vector1.y * vector2.x);

		return temp;
	}

	float Vector3::Dot(const Vector3 &vector1, const Vector3 &vector2)
	{
		float temp = (vector1.x * vector2.x) + (vector1.y * vector2.y) + (vector1.z * vector2.z);

		return temp;
	}
}