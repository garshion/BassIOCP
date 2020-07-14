#include "Polygon.h"
#include "Line.h"

Bass::Polygon::Polygon()
{
}

Bass::Polygon::~Polygon()
{
}

bool Bass::Polygon::IsClosed() const
{
	if (true == m_vecPoints.empty())
		return false;

	auto& vSP = m_vecPoints[0];
	auto& vEP = m_vecPoints[m_vecPoints.size() - 1];
	
	return IsZero(vSP.Distance2D(vEP));
}

bool Bass::Polygon::IsPolygon() const
{
	if (m_vecPoints.size() <= MIN_POLYGON_VERTEX_COUNT)
		return false;

	return IsClosed();
}

void Bass::Polygon::AddPoint(const Vec3 & vPos)
{
	m_vecPoints.push_back(vPos);
}

bool Bass::Polygon::RemovePointAt(size_t at)
{
	if (at >= m_vecPoints.size())
		return false;

	
	auto it = m_vecPoints.begin();
	for (size_t i = 0; i < at; ++i)
		++it;
	m_vecPoints.erase(it);
	return true;
}

bool Bass::Polygon::IsPointInShape(const Vec3 & vPos) const
{
	if (false == IsPolygon())
		return false;

	int nCross = 0;
	Vec3 vCrossPos;

	Line checkLine(vPos, vPos + Vec3::XAxis * DEFAULT_INFINITY_F32);

	for (size_t i = 1; i < m_vecPoints.size(); ++i)
	{
		Line ln(m_vecPoints[i - 1], m_vecPoints[i]);
		if (ELineCrossType::LINE_CROSS_POINT == ln.CheckLineCrossed(checkLine, vCrossPos))
			nCross++;
	}

	return ((nCross % 2) == 1);
}

void Bass::Polygon::Transform(const Matrix & mat)
{
	for (auto it = m_vecPoints.begin(); it != m_vecPoints.end(); ++it)
	{
		*it = mat * (*it);
	}
}

void Bass::Polygon::Move(const Vec3 & vPoint)
{
	for (auto it = m_vecPoints.begin(); it != m_vecPoints.end(); ++it)
	{
		*it += vPoint;
	}
}

Bass::Vec3 Bass::Polygon::GetCenter() const
{
	Vec3 vRet(0.0f, 0.0f);

	if (true == m_vecPoints.empty())
		return vRet;

	double dX = 0.0;
	double dY = 0.0;

	for (auto& vPos : m_vecPoints)
	{
		dX += vPos.x;
		dY += vPos.y;
	}

	dX /= m_vecPoints.size();
	dY /= m_vecPoints.size();

	return Vec3((float)dX, (float)dY);
}
