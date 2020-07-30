#include "Box.h"
#include "MathCommon.h"
#include "Matrix.h"

Bass::Box::Box()
{
	m_vMax.Set(-DEFAULT_INFINITY, -DEFAULT_INFINITY);
	m_vMin.Set(DEFAULT_INFINITY, DEFAULT_INFINITY);
}

Bass::Box::Box(const float & left, const float & right, const float & top, const float & bottom)
{
	Vec3 vPos;
	vPos.Set(left, top);
	AddMinMax(vPos);
	vPos.Set(right, bottom);
	AddMinMax(vPos);
}

Bass::Box::~Box()
{
}

bool Bass::Box::IsPointInShape(const Vec3 & vPos) const
{
	if (vPos.x > m_vMax.x
		|| vPos.x < m_vMin.x
		|| vPos.y > m_vMax.y
		|| vPos.y < m_vMin.y)
		return false;
	return true;
}

void Bass::Box::Transform(const Matrix & mat)
{
	m_vMax = mat * m_vMax;
}

void Bass::Box::Move(const Vec3 & vPoint)
{
	m_vMin += vPoint;
	m_vMax += vPoint;
}

Bass::Vec3 Bass::Box::GetCenter() const
{
	return (m_vMin + m_vMax) / 2.0f;
}

void Bass::Box::AddMinMax(const Vec3 & vPos)
{
	if (m_vMin.x > vPos.x) m_vMin.x = vPos.x;
	if (m_vMin.y > vPos.y) m_vMin.y = vPos.y;
	if (m_vMin.z > vPos.z) m_vMin.z = vPos.z;
	if (m_vMax.x < vPos.x) m_vMax.x = vPos.x;
	if (m_vMax.y < vPos.y) m_vMax.y = vPos.y;
	if (m_vMax.z < vPos.z) m_vMax.z = vPos.z;
}

void Bass::Box::AddMinMax(const Box & box)
{
	AddMinMax(box.m_vMax);
	AddMinMax(box.m_vMin);
}

double Bass::Box::Width() const
{
	return m_vMax.x - m_vMin.x;
}

double Bass::Box::Height() const
{
	return m_vMax.y - m_vMin.y;
}
