#include "AABB.h"

namespace framework9
{
	// AABB2d
	AABB2d::AABB2d()
		: min()
		, max()
	{
	}
	AABB2d::AABB2d(Vector2 _min, Vector2 _max)
		: min(_min)
		, max(_max)
	{
	}
	AABB2d::AABB2d(float minX, float minY, float maxX, float maxY)
		: min(minX, minY)
		, max(maxX, maxY)
	{
	}
	AABB2d::AABB2d(const AABB2d &aabb)
		: min(aabb.min)
		, max(aabb.max)
	{
	}
	AABB2d::~AABB2d()
	{
	}

	AABB2d& AABB2d::operator +=(const Vector2 &position)
	{
		min += position;
		max += position;

		return *this;
	}

	AABB2d& AABB2d::operator -=(const Vector2 &position)
	{
		min -= position;
		max -= position;

		return *this;
	}

	AABB2d AABB2d::operator +(const Vector2 &position) const
	{
		AABB2d temp(*this);

		temp += position;

		return temp;
	}

	AABB2d AABB2d::operator -(const Vector2 &position) const
	{
		AABB2d temp(*this);

		temp -= position;

		return temp;
	}

	// AABB2d
	AABB3d::AABB3d()
		: min()
		, max()
	{
	}
	AABB3d::AABB3d(Vector3 _min, Vector3 _max)
		: min(_min)
		, max(_max)
	{
	}
	AABB3d::AABB3d(float minX, float minY, float minZ, float maxX, float maxY, float maxZ)
		: min(minX, minY, minZ)
		, max(maxX, maxY, maxZ)
	{
	}
	AABB3d::AABB3d(const AABB3d &aabb)
		: min(aabb.min)
		, max(aabb.max)
	{
	}
	AABB3d::~AABB3d()
	{
	}

	AABB3d& AABB3d::operator +=(const Vector3 &position)
	{
		min += position;
		max += position;

		return *this;
	}

	AABB3d& AABB3d::operator -=(const Vector3 &position)
	{
		min -= position;
		max -= position;

		return *this;
	}

	AABB3d AABB3d::operator +(const Vector3 &position) const
	{
		AABB3d temp(*this);

		temp += position;

		return temp;
	}

	AABB3d AABB3d::operator -(const Vector3 &position) const
	{
		AABB3d temp(*this);

		temp -= position;

		return temp;
	}
}