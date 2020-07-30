#include "MathCommon.h"

bool Bass::IsSame(const double& v1, const double& v2, const double& tol) noexcept
{
	if (fabs(v1 - v2) < tol)
		return true;
	return false;
}

bool Bass::IsSame(const float& v1, const float& v2, const float& tol) noexcept
{
	if (fabsf(v1 - v2) < tol)
		return true;
	return false;
}

bool Bass::IsZero(const double& val, const double& tol) noexcept
{
	return IsSame(val, tol);
}

bool Bass::IsZero(const float& val, const float& tol) noexcept
{
	return IsSame(val, tol);
}

bool Bass::IsValid(const double& val)
{
	if (true == isnan(val)
		|| true == isinf(val))
		return false;
	return true;
}

bool Bass::IsValid(const float& val)
{
	if (true == isnan(val)
		|| true == isinf(val))
		return false;
	return true;
}



Bass::Degree Bass::RadianToDegree(const Bass::Radian& rad)
{
	return rad * PI_DEGREE * DIV_PI;
}

Bass::Radian Bass::DegreeToRadian(const Bass::Degree& deg)
{
	return deg * PI * DIV_PI_DEGREE;
}

Bass::Degree32 Bass::RadianToDegree(const Bass::Radian32& rad)
{
	return rad * PI_DEGREE_32 * DIV_PI_32;
}

Bass::Radian32 Bass::DegreeToRadian(const Bass::Degree32& deg)
{
	return deg * PI_32 * DIV_PI_DEGREE_32;
}

Bass::Degree Bass::DegreeNormalize(const Bass::Degree& deg)
{
	double dRet = fmod(deg, PI2_DEGREE);
	if (dRet < 0.0)
		dRet += PI2_DEGREE;
	return dRet;
}

Bass::Degree32 Bass::DegreeNormalize(const Bass::Degree32& deg)
{
	float fRet = fmodf(deg, PI2_DEGREE_32);
	if (fRet < 0.0f)
		fRet += PI2_DEGREE_32;
	return fRet;
}

Bass::Radian Bass::RadianNormalize(const Bass::Radian& rad)
{
	double dRet = fmod(rad, PI2);
	if (dRet < 0.0)
		dRet += PI2;
	return dRet;
}

Bass::Radian32 Bass::RadianNormalize(const Bass::Radian32& rad)
{
	float fRet = fmodf(rad, PI2_32);
	if (fRet < 0.0f)
		fRet += PI2_32;
	return fRet;
}

Bass::Meter Bass::ToMeter(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val;
	case EDistance::CentiMeter: return val * 0.01;
	case EDistance::MilliMeter: return val * 0.001;
	case EDistance::KiloMeter: return val * 1000.0;
	case EDistance::Feet: return val * 0.3048;
	case EDistance::FlightLevel: return val * 30.48;
	case EDistance::Mile: return val * 1609.34;
	case EDistance::NauticalMile: return val * 1852.0;
	case EDistance::Inch: return val * 0.0254;
	case EDistance::Yard: return val * 0.9144;
	default:
		break;
	}

	return Meter(0);
}

Bass::CentiMeter Bass::ToCentiMeter(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 100.0;
	case EDistance::CentiMeter: return val;
	case EDistance::MilliMeter: return val * 0.1;
	case EDistance::KiloMeter: return val * 100000.0;
	case EDistance::Feet: return val * 30.48;
	case EDistance::FlightLevel: return val * 3048.0;
	case EDistance::Mile: return val * 160934.0;
	case EDistance::NauticalMile: return val * 185200.0;
	case EDistance::Inch: return val * 2.54;
	case EDistance::Yard: return val * 91.44;
	default:
		break;
	}

	return CentiMeter(0);
}

Bass::MilliMeter Bass::ToMilliMeter(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 1000.0;
	case EDistance::CentiMeter: return val * 10.0;
	case EDistance::MilliMeter: return val;
	case EDistance::KiloMeter: return val * 1000000.0;
	case EDistance::Feet: return val * 304.8;
	case EDistance::FlightLevel: return val * 30480.0;
	case EDistance::Mile: return val * 1609340.0;
	case EDistance::NauticalMile: return val * 1852000.0;
	case EDistance::Inch: return val * 25.4;
	case EDistance::Yard: return val * 914.4;
	default:
		break;
	}

	return MilliMeter(0);
}

Bass::KiloMeter Bass::ToKiloMeter(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 0.001;
	case EDistance::CentiMeter: return val * 0.00001;
	case EDistance::MilliMeter: return val * 0.000001;
	case EDistance::KiloMeter: return val;
	case EDistance::Feet: return val * 0.0003048;
	case EDistance::FlightLevel: return val * 0.03048;
	case EDistance::Mile: return val * 1.60934;
	case EDistance::NauticalMile: return val * 1.852;
	case EDistance::Inch: return val * 0.0000254;
	case EDistance::Yard: return val * 0.0009144;
	default:
		break;
	}

	return KiloMeter(0);
}

Bass::Feet Bass::ToFeet(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 3.28084;
	case EDistance::CentiMeter: return val * 0.0328084;
	case EDistance::MilliMeter: return val * 0.00328084;
	case EDistance::KiloMeter: return val * 3280.84;
	case EDistance::Feet: return val;
	case EDistance::FlightLevel: return val * 100.0;
	case EDistance::Mile: return val * 5280.0;
	case EDistance::NauticalMile: return val * 6076.12;
	case EDistance::Inch: return val * 0.0833333;
	case EDistance::Yard: return val * 3.0;
	default:
		break;
	}

	return Feet(0);
}

Bass::FlightLevel Bass::ToFL(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 0.0328084;
	case EDistance::CentiMeter: return val * 0.000328084;
	case EDistance::MilliMeter: return val * 0.0000328084;
	case EDistance::KiloMeter: return val * 32.8084;
	case EDistance::Feet: return val * 0.01;
	case EDistance::FlightLevel: return val;
	case EDistance::Mile: return val * 52.80;
	case EDistance::NauticalMile: return val * 60.7612;
	case EDistance::Inch: return val * 0.000833333;
	case EDistance::Yard: return val * 0.03;
	default:
		break;
	}

	return FlightLevel(0);
}

Bass::Mile Bass::ToMile(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val / 1609.34;
	case EDistance::CentiMeter: return val / 160934.0;
	case EDistance::MilliMeter: return val / 1609340.0;
	case EDistance::KiloMeter: return val / 1.60934;
	case EDistance::Feet: return val / 5280;
	case EDistance::FlightLevel: return val / 52.80;
	case EDistance::Mile: return val;
	case EDistance::NauticalMile: return val * 1.15078;
	case EDistance::Inch: return val / 63360.0;
	case EDistance::Yard: return val / 1760.0;
	default:
		break;
	}

	return Mile(0);
}

Bass::NauticalMile Bass::ToKN(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val / 1852.0;
	case EDistance::CentiMeter: return val / 185200.0;
	case EDistance::MilliMeter: return val / 1852000.0;
	case EDistance::KiloMeter: return val / 1.852;
	case EDistance::Feet: return val / 6076.12;
	case EDistance::FlightLevel: return val / 60.7612;
	case EDistance::Mile: return val * 0.868976;
	case EDistance::NauticalMile: return val;
	case EDistance::Inch: return val / 72913.4;
	case EDistance::Yard: return val / 2025.37;
	default:
		break;
	}

	return NauticalMile(0);
}

Bass::Inch Bass::ToInch(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 39.3701;
	case EDistance::CentiMeter: return val * 0.393701;
	case EDistance::MilliMeter: return val * 0.0393701;
	case EDistance::KiloMeter: return val * 39370.1;
	case EDistance::Feet: return val * 12.0;
	case EDistance::FlightLevel: return val * 1200.0;
	case EDistance::Mile: return val * 63360.0;
	case EDistance::NauticalMile: return val * 72913.4;
	case EDistance::Inch: return val;
	case EDistance::Yard: return val * 36.0;
	default:
		break;
	}
	return Inch(0);
}

Bass::Yard Bass::ToYard(const double& val, const EDistance& inputType)
{
	switch (inputType)
	{
	case EDistance::Meter: return val * 1.09361;
	case EDistance::CentiMeter: return val * 0.0109361;
	case EDistance::MilliMeter: return val * 0.00109361;
	case EDistance::KiloMeter: return val * 1093.61;
	case EDistance::Feet: return val / 3.0;
	case EDistance::FlightLevel: return val * 100.0 / 3.0;
	case EDistance::Mile: return val * 1760.0;
	case EDistance::NauticalMile: return val * 2025.37;
	case EDistance::Inch: return val / 36.0;
	case EDistance::Yard: return val;
	default:
		break;
	}
	return Yard(0);
}
