#pragma once
#include <cmath>

namespace Bass
{

	// 원주율 관련
	constexpr double PI = 3.14159265358979323846264338327950288419716939937510;			// 배정밀도 원주율
	constexpr float PI_32 = 3.1415927f;	// 단정밀도 원주율
	constexpr double DIV_PI = 1.0 / PI;
	constexpr float DIV_PI_32 = 1.0f / PI_32;

	constexpr double PI2 = PI * 2.0;
	constexpr float PI2_32 = PI_32 * 2.0f;

	constexpr double PI_DEGREE = 180.0;
	constexpr double PI2_DEGREE = 360.0;
	constexpr double DIV_PI_DEGREE = 1.0 / 180.0;

	constexpr float PI_DEGREE_32 = 180.0f;
	constexpr float PI2_DEGREE_32 = 360.0f;
	constexpr float DIV_PI_DEGREE_32 = 1.0f / 180.0f;

	// 근사 오차값
	constexpr double TOLORANCE = 0.000000000000001;
	constexpr float TOLORANCE_32 = 0.000001f;

	// 최대치 체크
	constexpr double DEFAULT_INFINITY = 1.e15;
	constexpr float DEFAULT_INFINITY_F32 = 1.e6f;


	bool IsSame(const double& v1, const double& v2, const double& tol = TOLORANCE) noexcept;
	bool IsSame(const float& v1, const float& v2, const float& tol = TOLORANCE_32) noexcept;
	bool IsZero(const double& val, const double& tol = TOLORANCE) noexcept;
	bool IsZero(const float& val, const float& tol = TOLORANCE_32) noexcept;

	double RadianToDegree(const double& rad);
	double DegreeToRadian(const double& deg);
	float RadianToDegree(const float& rad);
	float DegreeToRadian(const float& deg);

	double DegreeNormalize(const double& deg);	// 0~359
	float DegreeNormalize(const float& deg);
	double RadianNormalize(const double& rad);
	float RadianNormalize(const float& rad);

	bool IsValid(const double& val);
	bool IsValid(const float& val);
}