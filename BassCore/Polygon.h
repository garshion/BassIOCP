#pragma once
#include "Shape.h"
#include <vector>

namespace Bass
{
	constexpr int MIN_POLYGON_VERTEX_COUNT = 3;

	class Polygon : Shape
	{
	public:
		Polygon();
		virtual ~Polygon();
		
		bool IsClosed() const;
		bool IsPolygon() const;
		void AddPoint(const Vec3& vPos);
		bool RemovePointAt(size_t at);

		virtual bool IsPointInShape(const Vec3& vPos) const;
		virtual void Transform(const Matrix& mat);
		virtual void Move(const Vec3& vPoint);
		virtual Vec3 GetCenter() const;

	private:
		std::vector<Vec3> m_vecPoints;

	};

}