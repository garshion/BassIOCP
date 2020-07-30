#pragma once
#include "Vec3.h"

namespace Bass
{
	class Matrix;
	class Shape
	{
	public:
		Shape() {};
		virtual ~Shape() {};
		virtual bool IsPointInShape(const Vec3& vPos) const = 0;		// �ش� ���� ��� �ȿ� �����ϴ���?
		virtual void Transform(const Matrix& mat) = 0;					// ��Ʈ���� ����
		virtual void Move(const Vec3& vPoint) = 0;						// vPoint ��ŭ �̵� (z ����)
		virtual Vec3 GetCenter() const = 0;								// �ش� ����� �߽����� ����
	};
}