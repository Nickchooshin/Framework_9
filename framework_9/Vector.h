#ifndef _MATH_CLASS_
#define _MATH_CLASS_

namespace framework9
{
	typedef struct Vector2
	{
	public:
		float x;
		float y;

	public:
		Vector2();
		Vector2(const Vector2 &vector);
		Vector2(float x, float y);

		Vector2& operator +=(const Vector2 &vector);
		Vector2& operator -=(const Vector2 &vector);
		Vector2& operator *=(float scalar);
		Vector2& operator /=(float scalar);

		Vector2 operator +() const;
		Vector2 operator -() const;

		Vector2 operator +(const Vector2 &vector) const;
		Vector2 operator -(const Vector2 &vector) const;
		Vector2 operator *(float scalar) const;
		Vector2 operator /(float scalar) const;

		bool operator ==(const Vector2 &vector) const;
		bool operator !=(const Vector2 &vector) const;

		Vector2 Normalize() const;

		static float Dot(const Vector2 &vector1, const Vector2 &vector2);
	} Vector2;

	typedef struct Vector3
	{
	public:
		float x;
		float y;
		float z;

	public:
		Vector3();
		Vector3(const Vector3 &vector);
		Vector3(float x, float y, float z);

		Vector3& operator +=(const Vector3 &vector);
		Vector3& operator -=(const Vector3 &vector);
		Vector3& operator *=(float scalar);
		Vector3& operator /=(float scalar);

		Vector3 operator +() const;
		Vector3 operator -() const;

		Vector3 operator +(const Vector3 &vector) const;
		Vector3 operator -(const Vector3 &vector) const;
		Vector3 operator *(float scalar) const;
		Vector3 operator /(float scalar) const;

		bool operator ==(const Vector3 &vector) const;
		bool operator !=(const Vector3 &vector) const;

		Vector3 Normalize() const;

		static Vector3 Cross(const Vector3 &vector1, const Vector3 &vector2);
		static float Dot(const Vector3 &vector1, const Vector3 &vector2);
	} Vector3;
}

#endif