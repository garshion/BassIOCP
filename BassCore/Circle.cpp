#include "Circle.h"
#include "Matrix.h"
#include "MathCommon.h"


Bass::Circle::Circle()
{
}

Bass::Circle::Circle(const Vec3 & vPos, const double& radius)
{
	m_vPos = vPos;
	m_fRadius = radius;
}

Bass::Circle::Circle(const double& x, const double& y, const double& radius)
{
	m_vPos.Set(x, y);
	m_fRadius = radius;
}

Bass::Circle::~Circle()
{
}

bool Bass::Circle::IsPointInShape(const Vec3 & vPos)
{
	return m_vPos.Distance(vPos) <= m_fRadius;
}

void Bass::Circle::Transform(const Matrix & mat)
{
	m_vPos = mat * m_vPos;
}

void Bass::Circle::Move(const Vec3 & vPoint)
{
	m_vPos += vPoint;
}

Bass::Vec3 Bass::Circle::GetCenter() const
{
	return m_vPos;
}
