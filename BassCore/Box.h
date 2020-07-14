#pragma once
#include "Shape.h"
namespace Bass
{
	class Box : Shape
	{
	public:
		Box();
		Box(const float& left, const float& right, const float& top, const float& bottom);
		virtual ~Box();

		virtual bool IsPointInShape(const Vec3& vPos) const;
		virtual void Transform(const Matrix& mat);
		virtual void Move(const Vec3& vPoint);
		virtual Vec3 GetCenter() const;

		void AddMinMax(const Vec3& vPos);
		void AddMinMax(const Box& box);

		double Width() const;
		double Height() const;

	private:
		Vec3 m_vMin;
		Vec3 m_vMax;
	};

}