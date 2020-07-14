#include "Line.h"

Bass::Line::Line()
{
}

Bass::Line::Line(const Vec3 & sp, const Vec3 & ep)
{
	m_vSP.Set(sp);
	m_vEP.Set(ep);
	m_vSP.z = 0;
	m_vEP.z = 0;
}

Bass::Line::Line(const double & x1, const double & y1, const double & x2, const double & y2)
{
	m_vSP.Set(x1, y1);
	m_vEP.Set(x2, y2);
}

Bass::Line::~Line()
{
}

double Bass::Line::Length() const
{
	return m_vSP.Distance(m_vEP);
}

Bass::Vec3 & Bass::Line::StartPoint()
{
	return m_vSP;
}

Bass::Vec3 & Bass::Line::EndPoint()
{
	return m_vEP;
}

bool Bass::Line::PointOnLine(const Vec3 & vPos, const double & dTol) const
{
	if (true == IsZero(Length(), dTol))
		return false;

	double dDistance = fabs((m_vEP.y - m_vSP.y) * (vPos.x - m_vSP.x) - (vPos.y - m_vSP.y) * (m_vEP.x - m_vSP.x));

	return IsZero(dDistance);
}

const Bass::ELineCrossType Bass::Line::CheckLineCrossed(const Line & ln, Vec3 & o_vCrossPoint, const double & dTol) const
{
	// 두 선중 하나라도 길이가 0일 경우
	if (true == IsZero(Length(), dTol)
		|| true == IsZero(ln.Length(), dTol))
		return ELineCrossType::LINE_CROSS_NONE;

	// 아래 공식 출처 : http://www.gisdeveloper.co.kr/?p=89

	// this sp : A, this ep : B, ln.sp = C, ln.ep = D
	Vec3 vAB = m_vEP - m_vSP;
	Vec3 vCD = ln.m_vEP - ln.m_vSP;
	Vec3 vAC = ln.m_vSP - m_vSP;

	double dT = vCD.x * vAC.y - vCD.y * vAC.x;
	double dS = vAB.x * vAC.y - vAB.y * vAC.x;
	double dUnder = (vCD.y * vAB.x) - (vCD.x * vAB.y);

	if (true == IsZero(dUnder))
	{
		if (true == IsZero(dT)
			&& true == IsZero(dS))
		{
			return ELineCrossType::LINE_CROSS_SAME;
		}
		return ELineCrossType::LINE_CROSS_PARALLEL;
	}

	dT /= dUnder;
	dS /= dUnder;

	if(dT < 0.0
		|| dT > 1.0
		|| dS < 0.0
		|| dS > 1.0)
		return ELineCrossType::LINE_CROSS_NONE;

	o_vCrossPoint.x = (float)(m_vSP.x + (dT * vAB.x));
	o_vCrossPoint.y = (float)(m_vSP.y + (dT * vAB.y));
	o_vCrossPoint.z = 0.0f;

	return ELineCrossType::LINE_CROSS_POINT;
}

bool Bass::Line::PointOnLine(Line ln, Vec3 vPos, const double & dTol)
{
	return ln.PointOnLine(vPos, dTol);
}

const Bass::ELineCrossType Bass::Line::CheckLineCrossed(Line ln1, Line ln2, Vec3 & o_vCrossPoint, const double & dTol)
{
	return ln1.CheckLineCrossed(ln2, o_vCrossPoint, dTol);
}

