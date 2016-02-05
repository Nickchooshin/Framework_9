#ifndef _AABB_H_
#define _AABB_H_

#include "Vector.h"

namespace framework9
{
	class AABB2d
	{
	public:
		Vector2 min;
		Vector2 max;

	public:
		AABB2d();
		AABB2d(Vector2 _min, Vector2 _max);
		AABB2d(float minX, float minY, float maxX, float maxY);
		AABB2d(const AABB2d &aabb);
		~AABB2d();

		AABB2d& operator +=(const Vector2 &position);
		AABB2d& operator -=(const Vector2 &position);

		AABB2d operator +(const Vector2 &position) const;
		AABB2d operator -(const Vector2 &position) const;
	};

	class AABB3d
	{
	public:
		Vector3 min;
		Vector3 max;

	public:
		AABB3d();
		AABB3d(Vector3 _min, Vector3 _max);
		AABB3d(float minX, float minY, float minZ, float maxX, float maxY, float maxZ);
		AABB3d(const AABB3d &aabb);
		~AABB3d();

		AABB3d& operator +=(const Vector3 &position);
		AABB3d& operator -=(const Vector3 &position);

		AABB3d operator +(const Vector3 &position) const;
		AABB3d operator -(const Vector3 &position) const;
	};
}

#endif