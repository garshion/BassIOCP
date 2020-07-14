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

double Bass::RadianToDegree(const double& rad)
{
	return rad * PI_DEGREE / PI;
}

double Bass::DegreeToRadian(const double& deg)
{
	return deg * PI / PI_DEGREE;
}

float Bass::RadianToDegree(const float& rad)
{
	return rad * PI_DEGREE_32 / PI_32;
}

float Bass::DegreeToRadian(const float& deg)
{
	return deg * PI_32 / PI_DEGREE_32;
}

double Bass::DegreeNormalize(const double& deg)
{
	double dRet = fmod(deg, PI2_DEGREE);
	if (dRet < 0.0)
		dRet += PI2_DEGREE;
	return dRet;
}

float Bass::DegreeNormalize(const float& deg)
{
	float fRet = fmodf(deg, PI2_DEGREE_32);
	if (fRet < 0.0f)
		fRet += PI2_DEGREE_32;
	return fRet;
}

double Bass::RadianNormalize(const double& rad)
{
	double dRet = fmod(rad, PI2);
	if (dRet < 0.0)
		dRet += PI2;
	return dRet;
}

float Bass::RadianNormalize(const float& rad)
{
	float fRet = fmodf(rad, PI2_32);
	if (fRet < 0.0f)
		fRet += PI2_32;
	return fRet;
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
