#pragma once
#include <cmath>

namespace Bass
{
	////////////////////////////////////////////////////////////////////////////////
	// 공통
	////////////////////////////////////////////////////////////////////////////////

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


	bool IsValid(const double& val);
	bool IsValid(const float& val);


	////////////////////////////////////////////////////////////////////////////////
	// 삼각함수 관련
	////////////////////////////////////////////////////////////////////////////////

	using Radian = double;
	using Degree = double;
	using Radian32 = float;
	using Degree32 = float;

	constexpr double PI = 3.14159265358979323846264338327950288419716939937510;			// 배정밀도 원주율
	constexpr float PI_32 = 3.1415927f;	// 단정밀도 원주율
	constexpr double DIV_PI = 1.0 / PI;
	constexpr float DIV_PI_32 = 1.0f / PI_32;

	constexpr double PI2 = PI * 2.0;
	constexpr float PI2_32 = PI_32 * 2.0f;

	constexpr Degree PI_DEGREE = 180.0;
	constexpr Degree PI2_DEGREE = 360.0;
	constexpr double DIV_PI_DEGREE = 1.0 / 180.0;

	constexpr Degree32 PI_DEGREE_32 = 180.0f;
	constexpr Degree32 PI2_DEGREE_32 = 360.0f;
	constexpr float DIV_PI_DEGREE_32 = 1.0f / 180.0f;

	Degree RadianToDegree(const Radian& rad);
	Radian DegreeToRadian(const Degree& deg);
	Degree32 RadianToDegree(const Radian32& rad);
	Radian32 DegreeToRadian(const Degree32& deg);

	Degree DegreeNormalize(const Degree& deg);	// 0~359
	Degree32 DegreeNormalize(const Degree32& deg);
	Radian RadianNormalize(const Radian& rad);
	Radian32 RadianNormalize(const Radian32& rad);



	////////////////////////////////////////////////////////////////////////////////
	// 거리 관련
	////////////////////////////////////////////////////////////////////////////////

	enum class EDistance : int
	{	
		Meter,				
		CentiMeter,
		MilliMeter,
		KiloMeter,
		Feet,
		FlightLevel,
		Mile,
		NauticalMile,
		Inch,
		Yard,
	};

	using Meter = double;
	using CentiMeter = double;
	using MilliMeter = double;
	using KiloMeter = double;
	using Feet = double;
	using FlightLevel = double;
	using Mile = double;
	using NauticalMile = double;	// KN
	using Inch = double;
	using Yard = double;

	Meter ToMeter(const double& val, const EDistance& inputType);
	CentiMeter ToCentiMeter(const double& val, const EDistance& inputType);
	MilliMeter ToMilliMeter(const double& val, const EDistance& inputType);
	KiloMeter ToKiloMeter(const double& val, const EDistance& inputType);
	Feet ToFeet(const double& val, const EDistance& inputType);
	FlightLevel ToFL(const double& val, const EDistance& inputType);
	Mile ToMile(const double& val, const EDistance& inputType);
	NauticalMile ToKN(const double& val, const EDistance& inputType);
	Inch ToInch(const double& val, const EDistance& inputType);
	Yard ToYard(const double& val, const EDistance& inputType);




	////////////////////////////////////////////////////////////////////////////////
	// 속도 관련
	////////////////////////////////////////////////////////////////////////////////

	// Speed
	using Knot = double;
	using kmh = double;
	using ms = double;
	using Mach = double;


	////////////////////////////////////////////////////////////////////////////////
	// 온도 관련
	////////////////////////////////////////////////////////////////////////////////

	// Temperature
	using Celcius = double;		// 섭씨
	using Kelvin = double;		// 절대온도
	using Fahrenheit = double;	// 화씨

	////////////////////////////////////////////////////////////////////////////////
	// 무게 관련
	////////////////////////////////////////////////////////////////////////////////




}