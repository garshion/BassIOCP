#pragma once
#include "MathCommon.h"
#include "Vec3.h"

namespace Bass
{
	enum class ELineCrossType : int
	{
		LINE_CROSS_NONE = 0,		// 만나지 않음
		LINE_CROSS_POINT,			// 한 점에서 만남
		LINE_CROSS_PARALLEL,		// 평행
		LINE_CROSS_SAME,			// 겹침
	};

	class Vec3;
	class Line
	{
	public:
		Line();
		Line(const Vec3& sp, const Vec3& ep);
		Line(const double& x1, const double& y1, const double& x2, const double& y2);
		~Line();

		double Length() const;
		Vec3& StartPoint();
		Vec3& EndPoint();
		bool PointOnLine(const Vec3& vPos, const double& dTol = TOLORANCE) const;
		const ELineCrossType CheckLineCrossed(const Line& ln, Vec3& o_vCrossPoint, const double& dTol = TOLORANCE) const;

		// 특정 점이 라인 위에 있는지 체크
		static bool PointOnLine(Line ln, Vec3 vPos, const double& dTol = TOLORANCE);

		// 두 라인이 서로 교차하는지 체크
		static const ELineCrossType CheckLineCrossed(Line ln1, Line ln2, Vec3& o_vCrossPoint, const double& dTol = TOLORANCE);

	private:
		Vec3 m_vSP;
		Vec3 m_vEP;

	};
}
