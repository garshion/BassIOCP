#pragma once
#include "Shape.h"

namespace Bass
{

	class Circle : Shape
	{
	public:
		Circle();
		Circle(const Vec3& vPos, const float& radius);
		Circle(const float& x, const float& y, const float& radius);
		virtual ~Circle();

		virtual bool IsPointInShape(const Vec3& vPos);
		virtual void Transform(const Matrix& mat);
		virtual void Move(const Vec3& vPoint);
		virtual Vec3 GetCenter() const;

	private:
		Vec3 m_vPos;
		float m_fRadius = 0.0f;
	};

}