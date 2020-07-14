#pragma once

namespace Bass
{
	enum class ELineCrossType : int
	{
		LINE_CROSS_NONE = 0,		// 만나지 않음
		LINE_CROSS_POINT,			// 한 점에서 만남
		LINE_CROSS_PARALLEL,		// 평행
		LINE_CROSS_SAME,			// 겹침
	};

}