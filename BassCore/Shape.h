#pragma once
#include "Vec3.h"
#include "Matrix.h"
#include "MathCommon.h"

namespace Bass
{
	class Shape
	{
	public:
		Shape() {};
		virtual ~Shape() {};
		virtual bool IsPointInShape(const Vec3& vPos) const = 0;		// 해당 점이 모양 안에 존재하는지?
		virtual void Transform(const Matrix& mat) = 0;					// 매트릭스 적용
		virtual void Move(const Vec3& vPoint) = 0;						// vPoint 만큼 이동 (z 무시)
		virtual Vec3 GetCenter() const = 0;								// 해당 모양의 중심점을 얻어옴
	};
}