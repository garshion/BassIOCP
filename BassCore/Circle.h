#pragma once
#include "Shape.h"

namespace Bass
{

	class Circle : Shape
	{
	public:
		Circle();
		Circle(const Vec3& vPos, const double& radius);
		Circle(const double& x, const double& y, const double& radius);
		virtual ~Circle();

		virtual bool IsPointInShape(const Vec3& vPos);
		virtual void Transform(const Matrix& mat);
		virtual void Move(const Vec3& vPoint);
		virtual Vec3 GetCenter() const;

	private:
		Vec3 m_vPos;
		double m_fRadius = 0.0f;
	};

}